#pragma once
#include "pch.h"
#include "dimensional.h"
#include "point.h"
#include "rect.h"
#include "coga/io/serializable.h"

namespace coga
{
	template<typename COORD, typename RETURN, typename DATA>
	class rect_packer :
		public dimensional<COORD>,
		public serializable
	{
	protected:
		using rect = rect<COORD>;
		using point = point<COORD>;
	protected:
		// hopefully this is good enough
		struct rect_hash
		{
			size_t operator()(const rect& r) const
			{
				return (COGA_CAST(size_t, r.min.x) << 48) | (COGA_CAST(size_t, r.min.y) << 32) | (COGA_CAST(size_t, r.max.x) << 16) | r.max.y;
			}
		};
		struct rect_area_comparator
		{
			bool operator()(const rect& a, const rect& b) const
			{
				return a.get_area() > b.get_area();
			}
		};
	public:
		COGA_DCM(rect_packer);
		virtual ~rect_packer() {}
	public:
		virtual void save(output_file& out) const override
		{
			// save steps
			out.ulong(m_x_steps.size()).ulong(m_y_steps.size());
			for (COORD s : m_x_steps)
				out.uint(s);
			for (COORD s : m_y_steps)
				out.uint(s);

			// save rects
			out.ulong(m_starts.size()).ulong(m_used.size());
			for (const rect& r : m_starts)
				out.uint(r.min.x).uint(r.min.y).uint(r.max.x).uint(r.max.y);
			for (const rect& r : m_used)
				out.uint(r.min.x).uint(r.min.y).uint(r.max.x).uint(r.max.y);
		}
		virtual void load(input_file& in) override
		{
			// load steps
			size_t x_size = in.ulong(), y_size = in.ulong();
			for (size_t i = 0; i < x_size; i++)
				m_x_steps.insert(in.uint());
			for (size_t i = 0; i < y_size; i++)
				m_y_steps.insert(in.uint());
			m_x_max = *m_x_steps.rbegin();
			m_y_max = *m_y_steps.rbegin();

			// load rects
			size_t start_size = in.ulong(), used_size = in.ulong();
			for (size_t i = 0; i < start_size; i++)
				m_starts.insert({ { in.uint(), in.uint() }, { in.uint(), in.uint() } });
			for (size_t i = 0; i < used_size; i++)
				m_starts.insert({ { in.uint(), in.uint() }, { in.uint(), in.uint() } });
		}
		RETURN insert(COORD w, COORD h, const DATA* const data)
		{
			for (const rect& r : m_starts)
				if (r.get_w() >= w && r.get_h() >= h)
					return insert({ w, h }, r, data);

			// given rect doesn't fit in this atlas
			return {};
		}
	protected:
		constexpr static range_contains s_contains_exc = { false, false };
		constexpr static range_overlaps s_overlaps_inc = { { true, true }, { true, true } };
		constexpr static range_overlaps s_overlaps_exc = { { false, false }, { false, false } };
	protected:
		COORD m_x_max, m_y_max;
		std::set<COORD> m_x_steps, m_y_steps;
		std::multiset<rect, rect_area_comparator> m_starts, m_used;
	protected:
		rect_packer(COORD w, COORD h) :
			dimensional<COORD>(w, h),
			m_x_max(COGA_CAST(COORD, 0)),
			m_y_max(COGA_CAST(COORD, 0))
		{
			// start inserting at the origin
			m_x_steps.insert(0);
			m_y_steps.insert(0);
			// the whole texture is available
			m_starts.insert({ 0, 0, this->m_w, this->m_h });
		}
		rect_packer(input_file& in) :
			dimensional<COORD>(0, 0),
			m_x_max(COGA_CAST(COORD, 0)),
			m_y_max(COGA_CAST(COORD, 0))
		{
			load(in);
		}
	protected:
		virtual RETURN insert(const point& dims, const rect& spot, const DATA* const data)
		{
			// bounds of new rect
			const COORD x_start = spot.min.x, x_end = spot.min.x + dims.x;
			const COORD y_start = spot.min.y, y_end = spot.min.y + dims.y;
			m_x_max = glm::max(m_x_max, x_end);
			m_y_max = glm::max(m_y_max, y_end);
			// insert new steps
			m_x_steps.insert(x_end);
			m_y_steps.insert(y_end);
			// insert edges as steps to calculate the max area rectangle that can be formed at each point
			m_x_steps.insert(this->m_w);
			m_y_steps.insert(this->m_h);

			// insert new rect
			m_used.insert({ spot.min, { x_end, y_end } });

			// account for new rect
			update();

			// normalized texture coordinates of new rect
			return
			{
				{ 1.f * x_start / this->m_w, 1.f * x_end / this->m_w },
				{ 1.f * y_start / this->m_h, 1.f * y_end / this->m_h }
			};
		}
	private:
		void update()
		{
			// set of fewest possible rectangles, each having the largest possible area, such that all unused space left in the texture is covered by the union of the set
			std::vector<rect> rects = gen_rects(gen_points());

			// reset internal state
			m_starts.clear();
			m_x_steps.clear();
			m_y_steps.clear();
			for (const rect& r : rects)
			{
				m_starts.insert(r);
				m_x_steps.insert(r.min.x);
				m_y_steps.insert(r.min.y);
			}
		}
		std::vector<point> gen_points() const
		{
			std::vector<point> points;
			// generate all possible points of interest
			for (COORD x : m_x_steps)
			{
				for (COORD y : m_y_steps)
				{
					point p = { x, y };
					// if the current point is within an existing rectangle, ignore it
					bool contained = false;
					for (const rect& r : m_used)
						if (contained = r.contains(p, s_contains_exc))
							break;
					if (!contained)
						points.push_back(p);
				}
			}
			return points;
		}
		std::vector<rect> gen_rects(const std::vector<point>& points) const
		{
			// given points of interest, generate rects between every pair of points
			size_t index = 0;
			std::unordered_set<rect, rect_hash> possible;
			for (const point& p : points)
			{
				// cache the largest rect so far
				rect cur = { p, p };
				for (const point& q : points)
				{
					// create a rect between p and q (swap things around so that min remains the top-left corner and max remains the bottom-right corner)
					const point min = { glm::min(p.x, q.x), glm::min(p.y, q.y) };
					const point max = { glm::max(p.x, q.x), glm::max(p.y, q.y) };
					rect test = { min, max };

					// if p == q or this rect is smaller than the cached one
					if (test.get_area() == 0 || test.get_area() <= cur.get_area())
						continue;

					// if this rect intersects any used space, ignore it
					bool intersects = false;
					for (const rect& r : m_used)
					{
						intersects = test.intersects(r, (test.contains(r, s_overlaps_inc) ? s_overlaps_inc : s_overlaps_exc));
						/*MAGE_INFO("[<{}, {}>, <{}, {}>] vs [<{}, {}>, <{}, {}>] => {}", test.min.x, test.min.y, test.max.x, test.max.y, r.min.x, r.min.y, r.max.x, r.max.y, intersects);*/
						if (intersects)
							break;
					}

					// otherwise, this is the largest rect so far
					if (!intersects)
						cur = test;
				}
				if (cur.get_area() > 0)
					possible.insert(cur);
			}
			/*MAGE_INFO("POSSIBLE");
			for (auto& r : possible)
				MAGE_INFO("[<{}, {}>, <{}, {}>]", r.min.x, r.min.y, r.max.x, r.max.y);*/


			// filter generated rects such that the smallest list of rects that cover the same area remain; remove any rects that are inside other rects
			std::vector<rect> result;
			for (const rect& a : possible)
			{
				bool contained = false;
				for (const rect& b : possible)
					if (a != b && (contained = b.contains(a, s_overlaps_inc)))
						break;
				if (!contained)
					result.push_back(a);
			}
			return result;
		}
	};
}
