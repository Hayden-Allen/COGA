#pragma once
#include "pch.h"
#include "texture.h"
#include "coga/graphics/framebuffer.h"

namespace coga::gl
{
	class framebuffer : public coga::gfx::framebuffer<coga::gl::texture2d, const void* const, const texture_options&>
	{
	public:
		framebuffer(event_handler_container& c, s_type w, s_type h, const std::initializer_list<coga::gfx::framebuffer_attachment<coga::gl::texture2d, const void* const, const texture_options&>*>& attachments);
		COGA_DCM(framebuffer);
		virtual ~framebuffer()
		{
			COGA_CORE_TRACE("Delete FB {}", m_id);
			glDeleteFramebuffers(1, &m_id);
		}
	public:
		void update() override;
		void bind() const override
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		}
		void unbind() const override
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	};
}
