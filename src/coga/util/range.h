#pragma once
#include "pch.h"
#include "typed.h"
#include "coga/io/serializable.h"

namespace coga
{
	struct range_contains
	{
		bool left = false, right = false;
	};
	struct range_overlaps
	{
		range_contains min = {}, max = {};
	};



	template<typename T>
	class range : public typed<T>
	{
	public:
		range(const T& min, const T& max) :
			m_min(min),
			m_max(max)
		{
			COGA_CORE_ASSERT(min < max, "Range min ({}) must be < than max ({})", min, max);
		}
	public:
		void operator=(const range<T>& other)
		{
			m_min = other.m_min;
			m_max = other.m_max;
		}
		template<typename U = T>
		bool operator==(const range<U>& other) const
		{
			return m_min == COGA_CAST(T, other.m_min) && m_max == COGA_CAST(T, other.m_max);
		}
		template<typename U = T>
		bool contains(const U& value, const range_contains& params = {}) const
		{
			return (params.left ? m_min <= value : m_min < value) && (params.right ? m_max >= value : m_max > value);
		}
		template<typename U = T>
		bool contains(const range<U>& other, const range_overlaps& params = {}) const
		{
			return contains(other.m_min, params.min) && contains(other.m_max, params.max);
		}
		template<typename U = T>
		bool overlaps(const range<U>& other, const range_overlaps& params = {}) const
		{
			return contains(other.m_min, params.min) || contains(other.m_max, params.max);
		}
		template<typename U = T, typename R = T>
		U map_to(const U& value, const range<R>& target) const
		{
			float slope = 1.f * target.get_span() / get_span();
			return target.m_min + slope * (value - m_min);
		}
		template<typename U = T, typename R = T>
		U map_from(const U& value, const range<R>& source) const
		{
			return source.map_to(value, *this);
		}
		template<typename X = T, typename Y = T>
		glm::vec2 map_to(const glm::vec2& value, const range<X>& x, const range<Y>& y = x) const
		{
			return { map_to(value.x, x), map_to(value.y, y) };
		}
		template<typename X = T, typename Y = T>
		glm::vec2 map_from(const glm::vec2& value, const range<X>& x, const range<Y>& y = x) const
		{
			return { map_from(value.x, x), map_from(value.y, y) };
		}
		template<typename U = T>
		U get_min() const
		{
			return COGA_CAST(U, m_min);
		}
		template<typename U = T>
		U get_max() const
		{
			return COGA_CAST(U, m_max);
		}
		template<typename U = T>
		U get_span() const
		{
			return COGA_CAST(U, m_max - m_min);
		}
	private:
		T m_min, m_max;
	};
}
