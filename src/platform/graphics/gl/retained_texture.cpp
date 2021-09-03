#include "pch.h"
#include "retained_texture.h"

namespace coga::gl
{
	retained_texture2d::retained_texture2d(s_type w, s_type h, size_t count, const texture_options& options) :
		coga::gl::texture<coga::gfx::retained_texture2d, GL_TEXTURE_2D, size_t, const uint32_t* const>(options, w, h, count, nullptr)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), nullptr);
	}
	retained_texture2d::retained_texture2d(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options) :
		coga::gl::texture<coga::gfx::retained_texture2d, GL_TEXTURE_2D, size_t, const uint32_t* const>(options, w, h, count, data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
	void retained_texture2d::load(input_file& in)
	{
		coga::gfx::retained_texture2d::load(in);
		deserialize_texture_options(m_options, in);
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(m_options.target_format), m_w, m_h, 0, get_source_format(m_options.source_format), get_source_type(m_options.source_type), m_data);
	}
	void retained_texture2d::update(s_type x, s_type y, s_type w, s_type h, const void* const data)
	{
		coga::gfx::retained_texture2d::update(x, y, w, h, data);
		bind(0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, get_source_format(m_options.source_format), get_source_type(m_options.source_type), data);
	}
}
