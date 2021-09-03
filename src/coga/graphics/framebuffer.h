#pragma once
#include "pch.h"
#include "framebuffer_attachment.h"
#include "render_object.h"
#include "coga/event/event_handler.h"
#include "coga/event/event_handler_container.h"
#include "coga/util/dimensional.h"

namespace coga::gfx
{
	template<typename T, typename ... ARGS>
	class framebuffer :
		public render_object,
		public event_handler,
		public dimensional<uint32_t>
	{
	public:
		COGA_DCM(framebuffer);
		virtual ~framebuffer() {}
	public:
		virtual void update() = 0;
		bool on_window_resize(window_resize_event& e) override
		{
			m_w = e.get_w();
			m_h = e.get_h();
			update();

			for (framebuffer_attachment<T, ARGS...>* const a : m_attachments)
			{
				a->m_w = e.get_w();
				a->m_h = e.get_h();
				a->reset();
			}

			return false;
		}
	protected:
		std::vector<framebuffer_attachment<T, ARGS...>*> m_attachments;
	protected:
		framebuffer(event_handler_container& c, s_type w, s_type h, const std::initializer_list<framebuffer_attachment<T, ARGS...>*>& attachments) :
			dimensional<s_type>(w, h),
			m_attachments(attachments)
		{
			c.add(this);
		}
	};
}
