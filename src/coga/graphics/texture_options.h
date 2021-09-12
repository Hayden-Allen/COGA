#pragma once
#include "pch.h"
#include "coga/util/typed.h"

namespace coga::gfx
{
	enum class texture_min_filter
	{
		none = 0,
		nearest, linear, nearest_nearest, linear_nearest, nearest_linear, linear_linear
	};
	enum class texture_mag_filter
	{
		none = 0,
		nearest, linear
	};
	enum class texture_wrap_s
	{
		none = 0,
		clamp_edge, clamp_border, mirror_repeat, repeat, mirror_clamp_edge
	};
	enum class texture_wrap_t
	{
		none = 0,
		clamp_edge, clamp_border, mirror_repeat, repeat, mirror_clamp_edge
	};
	enum class texture_target_format
	{
		none = 0,
		rgba8
	};
	enum class texture_source_format
	{
		none = 0,
		rgba
	};
	enum class texture_source_type
	{
		none = 0,
		byte
	};



	// TODO should be revisited and further abstracted when new APIs are introduced
	struct texture_options
	{};
}
