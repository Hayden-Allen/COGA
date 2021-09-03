#pragma once
#include "pch.h"
#include "event.h"

namespace coga::gfx
{
	class renderer;
}



namespace coga
{
	/**
	 * Base
	 */
	class app_event : public event
	{
	public:
		COGA_DCM(app_event);
		MAGE_EVENT_CATEGORIES(event_category::app);
	public:
		float get_time() const
		{
			return m_time;
		}
		float get_delta_time() const
		{
			return m_delta_time;
		}
	protected:
		float m_time, m_delta_time;
	protected:
		app_event(float t, float dt) :
			m_time(t),
			m_delta_time(dt)
		{}
	};



	/**
	 * Implementation
	 */
	class app_tick_event final : public app_event
	{
	public:
		app_tick_event(float t, float dt) :
			app_event(t, dt)
		{}
		COGA_DCM(app_tick_event);
		MAGE_EVENT_TYPE(event_type::app_tick);
	};



	class app_draw_event final : public app_event
	{
	public:
		app_draw_event(float t, float dt) :
			app_event(t, dt)
		{}
		COGA_DCM(app_draw_event);
		MAGE_EVENT_TYPE(event_type::app_draw);
	};



	class app_render_event final : public app_event
	{
	public:
		app_render_event(float t, float dt) :
			app_event(t, dt)
		{}
		COGA_DCM(app_render_event);
		MAGE_EVENT_TYPE(event_type::app_render);
	};
}
