#include "pch.h"
#include "framebuffer_attachment.h"

namespace coga::gl
{
	framebuffer_color_attachment::framebuffer_color_attachment(s_type w, s_type h) :
		coga::gl::framebuffer_attachment<coga::gfx::framebuffer_color_attachment<coga::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>(w, h, nullptr, { .min_filter = coga::gfx::texture_min_filter::linear, .mag_filter = coga::gfx::texture_mag_filter::linear })
	{
		reset();
	}



	framebuffer_depth_attachment::framebuffer_depth_attachment(s_type w, s_type h) :
		coga::gl::framebuffer_attachment<coga::gfx::framebuffer_depth_attachment<coga::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>(w, h, nullptr, { .min_filter = coga::gfx::texture_min_filter::linear, .mag_filter = coga::gfx::texture_mag_filter::linear }
		)
	{
		reset();
	}
}
