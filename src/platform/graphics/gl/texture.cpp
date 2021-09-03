#include "pch.h"
#include "texture.h"
#include "coga/util/functions.h"

namespace coga::gl
{
	texture2d::texture2d(s_type w, s_type h, const void* const data, const texture_options& options) :
		coga::gl::texture<coga::gfx::texture2d, GL_TEXTURE_2D>(options, w, h)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
	void texture2d::update(s_type x, s_type y, s_type w, s_type h, const void* const data)
	{
		bind(0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, get_source_format(m_options.source_format), get_source_type(m_options.source_type), data);
	}



	texture2d_array::texture2d_array(s_type w, s_type h, s_type f, const void* const data, const texture_options& options) :
		coga::gl::texture<coga::gfx::texture2d_array, GL_TEXTURE_2D_ARRAY, coga::gfx::texture2d_array::s_type>(options, w, h, f)
	{
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, get_target_format(options.target_format), w, h, f, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
	void texture2d_array::update(s_type x, s_type y, s_type z, s_type w, s_type h, s_type d, const void* const data)
	{
		bind(0);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, x, y, z, w, h, d, get_source_format(m_options.source_format), get_source_type(m_options.source_type), data);
	}
}
