#pragma once
#include "pch.h"

namespace coga
{
	template<typename T>
	class typed
	{
	public:
		COGA_DCM(typed);
		typedef T s_type;
	protected:
		typed() {}
	};
}
