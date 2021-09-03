#pragma once
#include "pch.h"
#include "texture.h"
#include "coga/graphics/framebuffer_attachment.h"
#include "coga/util/dimensional.h"

namespace coga::gl
{
	static GLenum framebuffer_attachment_enum[] =
	{
		GL_NONE, GL_COLOR_ATTACHMENT0, GL_DEPTH_STENCIL_ATTACHMENT
	};
	static GLenum get_framebuffer_attachment_enum(coga::gfx::framebuffer_attachment_type type)
	{
		COGA_CORE_ASSERT(type != coga::gfx::framebuffer_attachment_type::none, "Invalid OpenGL framebuffer attachment type");
		return framebuffer_attachment_enum[COGA_CAST(size_t, type)];
	}



	template<typename T, typename ... ARGS>
	class framebuffer_attachment : public T
	{
	protected:
		using s_type = T::s_type;
	public:
		COGA_DCM(framebuffer_attachment);
		virtual ~framebuffer_attachment() {}
	protected:
		framebuffer_attachment(s_type w, s_type h, const ARGS& ... args) :
			T(w, h, args...)
		{}
	};



	class framebuffer_color_attachment final : public coga::gl::framebuffer_attachment<coga::gfx::framebuffer_color_attachment<coga::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>
	{
	public:
		framebuffer_color_attachment(s_type w, s_type h);
		COGA_DCM(framebuffer_color_attachment);
	protected:
		void reset() const override
		{
			bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_w, this->m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			unbind();
		}
	};



	class framebuffer_depth_attachment final : public coga::gl::framebuffer_attachment<coga::gfx::framebuffer_depth_attachment<coga::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>
	{
	public:
		framebuffer_depth_attachment(s_type w, s_type h);
		COGA_DCM(framebuffer_depth_attachment);
	protected:
		void reset() const override
		{
			bind(0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->m_w, this->m_h, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
			unbind();
		}
	};
}
