#pragma once
#include "pch.h"
#include "point.h"
#include "coga/io/serializable.h"

namespace coga
{
	template<typename T>
	struct rect
	{
		point<T> min, max;


		template<typename U = T>
		bool operator==(const rect<U>& other) const
		{
			return min == other.min && max == other.max;
		}
		template<typename U = T>
		bool operator!=(const rect<U>& other) const
		{
			return !operator==(other);
		}
		template<typename U = T>
		bool operator<(const rect<U>& other) const
		{
			return min < other.min && max < other.max;
		}
		template<typename U = T>
		bool intersects(const rect<U>& other, const range_overlaps& params = {}) const
		{
			range<T> tx = { min.x, max.x }, ox = { other.min.x, other.max.x };
			range<T> ty = { min.y, max.y }, oy = { other.min.y, other.max.y };
			return tx.overlaps(ox, params) && ty.overlaps(oy, params);
		}
		template<typename U = T>
		bool contains(const point<U>& p, const range_contains& params = {}) const
		{
			range<T> tx = { min.x, max.x }, ty = { min.y, max.y };
			return tx.contains(p.x, params) && ty.contains(p.y, params);
		}
		template<typename U = T>
		bool contains(const rect<U>& other, const range_overlaps& params = {}) const
		{
			range<T> tx = { min.x, max.x }, ox = { other.min.x, other.max.x };
			range<T> ty = { min.y, max.y }, oy = { other.min.y, other.max.y };
			return tx.contains(ox, params) && ty.contains(oy, params);
		}
		T get_w() const
		{
			return (max.x - min.x);
		}
		T get_h() const
		{
			return (max.y - min.y);
		}
		T get_area() const
		{
			return get_w() * get_h();
		}
	};
}
