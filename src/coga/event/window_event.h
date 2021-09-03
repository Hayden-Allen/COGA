#pragma once
#include "pch.h"
#include "event.h"
#include "coga/util/positional.h"
#include "coga/util/dimensional.h"

namespace coga
{
	/**
	 * Base
	 */
	class window_event : public event
	{
	public:
		COGA_DCM(window_event);
		MAGE_EVENT_CATEGORIES(event_category::window);
	protected:
		window_event() {}
	};



	/**
	 * Implementation
	 */
	class window_close_event final : public window_event
	{
	public:
		window_close_event() {}
		COGA_DCM(window_close_event);
		MAGE_EVENT_TYPE(event_type::window_close);
	};



	class window_focus_event final : public window_event
	{
	public:
		window_focus_event() {}
		COGA_DCM(window_focus_event);
		MAGE_EVENT_TYPE(event_type::window_focus);
	};



	class window_unfocus_event final : public window_event
	{
	public:
		window_unfocus_event() {}
		COGA_DCM(window_unfocus_event);
		MAGE_EVENT_TYPE(event_type::window_unfocus);
	};



	class window_resize_event final : public window_event, public dimensional<int>
	{
	public:
		window_resize_event(int x, int y) :
			dimensional<int>(x, y)
		{}
		COGA_DCM(window_resize_event);
	public:
		MAGE_EVENT_TYPE(event_type::window_resize);
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << get_name() << ": <" << m_w << ", " << m_h << ">";
			return ss.str();
		}
	};



	class window_move_event final : public window_event, public positional<int>
	{
	public:
		window_move_event(int x, int y) :
			positional<int>(x, y)
		{}
		COGA_DCM(window_move_event);
	public:
		MAGE_EVENT_TYPE(event_type::window_move);
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << get_name() << ": <" << m_x << ", " << m_y << ">";
			return ss.str();
		}
	};
}
