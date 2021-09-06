#pragma once
#include "pch.h"
#include "texture_options.h"
#include "coga/graphics/texture.h"

namespace coga::gl
{
	template<typename T, GLenum TARGET, typename ... ARGS>
	class texture : public T
	{
	public:
		COGA_DCM(texture);
		virtual ~texture()
		{
			glDeleteTextures(1, &this->m_id);
		}
		
		
		void bind(uint32_t slot) const
		{
			COGA_CORE_ASSERT(slot < 32, "Invalid OpenGL texture slot");
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(TARGET, this->m_id);
		}
		void unbind() const override
		{
			glBindTexture(TARGET, 0);
		}
	protected:
		texture_options m_options;


		texture(const texture_options& options, T::s_type w, T::s_type h, const ARGS& ... args) :
			T(w, h, args...),
			m_options(options)
		{
			glGenTextures(1, &this->m_id);
			bind(0);
			glTexParameteri(TARGET, GL_TEXTURE_MIN_FILTER, get_min_filter(options.min_filter));
			glTexParameteri(TARGET, GL_TEXTURE_MAG_FILTER, get_mag_filter(options.mag_filter));
			glTexParameteri(TARGET, GL_TEXTURE_WRAP_S, get_wrap_s(options.wrap_s));
			glTexParameteri(TARGET, GL_TEXTURE_WRAP_T, get_wrap_t(options.wrap_t));
		}
	};



	class texture2d : public coga::gl::texture<coga::gfx::texture2d, GL_TEXTURE_2D>
	{
	public:
		texture2d(s_type w, s_type h, const void* const data, const texture_options& options);
		COGA_DCM(texture2d);


		void update(s_type x, s_type y, s_type w, s_type h, const void* const data) override;
	};



	class texture2d_array : public coga::gl::texture<coga::gfx::texture2d_array, GL_TEXTURE_2D_ARRAY, coga::gfx::texture2d_array::s_type>
	{
	public:
		texture2d_array(s_type w, s_type h, s_type f, const void* const data, const texture_options& options);
		COGA_DCM(texture2d_array);

		
		void update(s_type x, s_type y, s_type z, s_type w, s_type h, s_type d, const void* const data) override;
	};
}
