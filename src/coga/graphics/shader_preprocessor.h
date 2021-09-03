#pragma once
#include "pch.h"

namespace coga::gfx
{
	struct shader_preprocessor
	{
	public:
		shader_preprocessor() {}
		COGA_DCM(shader_preprocessor);
		virtual ~shader_preprocessor() {}
	public:
		virtual std::string operator()(std::string& line) const
		{
			return line;
		}
	};
}
