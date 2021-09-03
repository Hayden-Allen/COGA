#pragma once
#include "pch.h"
#include "event.h"

namespace coga
{
	typedef std::function<void(event&)> event_callback_t;



	/**
	 * An object that creates and sends events to an event_handler
	 */
	class event_propagator
	{
	public:
		COGA_DCM(event_propagator);
	public:
		void invoke(event& e)
		{
			m_callback(e);
		}
		void set_event_callback(event_callback_t callback)
		{
			m_callback = callback;
		}
	protected:
		event_callback_t m_callback;
	protected:
		event_propagator() {}
	};
}
