#pragma once
#include "pch.h"
#include "event/event.h"
#include "event/event_handler.h"
#include "event/event_propagator.h"
#include "graphics/context.h"
#include "util/dimensional.h"
#include "util/color.h"

namespace coga
{
	// just to make parameters cleaner
	struct window_constructor
	{
		std::string title;
		uint32_t w, h;
		bool vsync;
		color<float> clear;
	};



	/**
	 * Interface for a non-mobile OS window
	 */
	class window :
		public event_propagator,
		public positional<uint32_t>,
		public dimensional<uint32_t>
	{
	public:
		COGA_DCM(window);
		virtual ~window()
		{
			delete m_context;
		}
	public:
		virtual void set_vsync(bool enabled) = 0;
		virtual void* get_native_window() const = 0;
		virtual std::string open_file_dialog(const char* filters) const = 0;
		virtual std::string open_multi_file_dialog(const char* filters) const = 0;
		virtual std::string save_file_dialog(const char* filters) const = 0;
		static window* create(const window_constructor& c);
		const std::string& get_title() const
		{
			return m_title;
		}
		bool is_vsync() const
		{
			return m_vsync;
		}
	protected:
		std::string m_title;
		bool m_vsync;
		color<float> m_clear;
		gfx::context* m_context;
	protected:
		window(const window_constructor& c) :
			positional<uint32_t>(0, 0),
			dimensional<uint32_t>(c.w, c.h),
			m_title(c.title),
			m_vsync(c.vsync),
			m_clear(c.clear),
			m_context(nullptr)
		{}
	protected:
		virtual std::string file_dialog(const char* name, const char* filters, uint32_t flags) const = 0;
	};
}

