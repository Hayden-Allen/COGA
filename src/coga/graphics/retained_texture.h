#pragma once
#include "pch.h"
#include "texture.h"

namespace coga::gfx
{
	/**
	 * A 2D texture stored on the GPU and in RAM.
	 */
	class retained_texture2d :
		public texture2d,
		public serializable
	{
	public:
		COGA_DCM(retained_texture2d);
		virtual ~retained_texture2d()
		{
			delete m_data;
		}
	public:
		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override
		{
			// make sure that specified sub-rectangle is valid
			check_bounds(x, y, w, h);
			// TODO hacky, needs to be changed if fp textures are ever supported
			const uint32_t* const idata = COGA_CAST(const uint32_t* const, data);
			// replace specified sub-rectangle with given data
			for (size_t i = 0; i < h; i++)
				for (size_t j = 0; j < w; j++)
					m_data[(y + i) * m_w + (x + j)] = idata[i * w + j];
		}
		void save(output_file& out) const override
		{
			save(out, 0, 0, m_w, m_h);
		}
		// save a "compressed" version of this texture, which consists of the smallest sub-rectangle such that all data written by the user is contained within it
		virtual void save(output_file& out, s_type x, s_type y, s_type w, s_type h) const
		{
			check_bounds(x, y, w, h);

			// physical size
			out.uint(m_w).uint(m_h).ulong(m_count);

			// written size
			out.uint(x).uint(y).uint(w).uint(h);
			for (size_t i = 0; i < h; i++)
				out.write(m_data + (y + i) * m_w + x, w);
		}
		void load(input_file& in) override
		{
			// physical size
			m_w = in.uint();
			m_h = in.uint();
			m_count = in.ulong();
			// allocated in the constructor, need to delete before allocating a new one
			delete[] m_data;
			m_data = new uint32_t[m_count];

			// written size
			const uint32_t x = in.uint(), y = in.uint(), w = in.uint(), h = in.uint();
			for (size_t i = 0; i < h; i++)
				in.read(m_data + (y + i) * m_w + x, w);
		}
	protected:
		size_t m_count;
		uint32_t* m_data;
	protected:
		retained_texture2d(s_type w, s_type h, size_t count, const uint32_t* const data) :
			texture2d(w, h),
			m_count(count),
			m_data(new uint32_t[count])
		{
			// fill with given data or 0s
			for (size_t i = 0; i < count; i++)
				m_data[i] = (data ? data[i] : 0);
		}
	protected:
		void check_bounds(s_type x, s_type y, s_type w, s_type h) const
		{
			COGA_CORE_ASSERT(x < m_w && y < m_h, "Invalid retained_texture2d lower bound <{}, {}> (must be < <{}, {}>)", x, y, m_w, m_h);
			// these are inclusive checks because the loops are exclusive (reach at most value - 1)
			COGA_CORE_ASSERT(x + w <= m_w && y + h <= m_h, "Invalid retained_texture2d upper bound <{}, {}> (must be < <{}, {}>)", x, y, m_w, m_h);
		}
	};
}
