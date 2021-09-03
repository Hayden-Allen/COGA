#pragma once
#include "pch.h"
#include "event.h"
#include "coga/util/positional.h"

namespace coga
{
	/**
	 * Base
	 */
	class mouse_event : public event
	{
	public:
		COGA_DCM(mouse_event);
		MAGE_EVENT_CATEGORIES(event_category::input | event_category::mouse);
	protected:
		mouse_event() {}
	};



	class mouse_vector_event : public mouse_event, public positional<float>
	{
	public:
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << this->get_name() << ": <" << m_x << ", " << m_y << ">";
			return ss.str();
		}
	protected:
		mouse_vector_event(float x, float y) :
			positional<float>(x, y)
		{}
	};



	class mouse_button_event : public mouse_event
	{
	public:
		COGA_DCM(mouse_button_event);
	public:
		MAGE_EVENT_CATEGORIES(event_category::input | event_category::mouse | event_category::mouse_button);
		int get_button() const
		{
			return m_button;
		}
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << this->get_name() << ": " << m_button;
			return ss.str();
		}
	protected:
		int m_button;
	protected:
		mouse_button_event(int button) :
			m_button(button)
		{}
	};



	/**
	 * Implementation
	 */
	class mouse_move_event final : public mouse_vector_event
	{
	public:
		mouse_move_event(float x, float y) :
			mouse_vector_event(x, y)
		{}
		COGA_DCM(mouse_move_event);
		MAGE_EVENT_TYPE(event_type::mouse_move);
	};



	class mouse_scroll_event final : public mouse_vector_event
	{
	public:
		mouse_scroll_event(float x, float y) :
			mouse_vector_event(x, y)
		{}
		COGA_DCM(mouse_scroll_event);
		MAGE_EVENT_TYPE(event_type::mouse_scroll);
	};



	class mouse_press_event final : public mouse_button_event
	{
	public:
		mouse_press_event(int button) :
			mouse_button_event(button)
		{}
		COGA_DCM(mouse_press_event);
		MAGE_EVENT_TYPE(event_type::mouse_press);
	};



	class mouse_release_event final : public mouse_button_event
	{
	public:
		mouse_release_event(int button) :
			mouse_button_event(button)
		{}
		COGA_DCM(mouse_release_event);
		MAGE_EVENT_TYPE(event_type::mouse_release);
	};
}
