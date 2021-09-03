#pragma once
#include "pch.h"
#include "texture.h"
#include "texture_options.h"
#include "coga/graphics/retained_texture.h"

namespace coga::gl
{
	class retained_texture2d : public coga::gl::texture<coga::gfx::retained_texture2d, GL_TEXTURE_2D, size_t, const uint32_t* const>
	{
	public:
		retained_texture2d(s_type w, s_type h, size_t count, const texture_options& options);
		retained_texture2d(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options);
		COGA_DCM(retained_texture2d);


		void load(input_file& in) override;
		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override;
		void save(output_file& out) const override
		{
			coga::gfx::retained_texture2d::save(out);
			serialize_texture_options(m_options, out);
		}
		void save(output_file& out, s_type x, s_type y, s_type w, s_type h) const override
		{
			coga::gfx::retained_texture2d::save(out, x, y, w, h);
			serialize_texture_options(m_options, out);
		}
	};
}
