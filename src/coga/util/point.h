#pragma once
#include "pch.h"

namespace coga
{
	template<typename T>
	struct point
	{
		T x, y;


		template<typename U = T>
		bool operator==(const point<U>& other) const
		{
			return x == other.x && y == other.y;
		}
		template<typename U = T>
		bool operator<(const point<U>& other) const
		{
			return x < other.x && y < other.y;
		}
	};
}
