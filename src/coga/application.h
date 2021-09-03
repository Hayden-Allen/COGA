#pragma once
#include "pch.h"
#include "event/app_event.h"
#include "event/event_handler.h"
#include "event/window_event.h"
#include "graphics/renderer.h"
#include "layer/layer_stack.h"
#include "log.h"
#include "window.h"

namespace coga
{
	/**
	 * Main driver class. Must be implemented in the client.
	 */
	class application : public event_handler
	{
	public:
		COGA_DCM(application);
		virtual ~application()
		{
			delete m_window;
		}
	public:
		void run();
		static application& get()
		{
			return *s_instance;
		}
		window& get_window()
		{
			return *m_window;
		}
		const window& get_window() const
		{
			return *m_window;
		}
		void close()
		{
			m_running = false;
		}
	protected:
		bool m_running;
		float m_time, m_delta_time;
		layer_stack m_layer_stack;
		window* m_window;
	protected:
		application(const window_constructor& data);
	protected:
		/**
		 * Simple wrappers for the layer_stack
		 */
		void attach_layer(layer* const layer)
		{
			m_layer_stack.attach(layer);
		}
		void detach_layer(layer* const layer)
		{
			m_layer_stack.detach(layer);
		}
		void attach_layer_top(layer* const layer)
		{
			m_layer_stack.attach_top(layer);
		}
		void detach_layer_top(layer* const layer)
		{
			m_layer_stack.detach_top(layer);
		}
		// terminate execution when the window is closed
		bool on_window_close(window_close_event& e) override
		{
			m_running = false;
			return true;
		}
		void on_event(coga::event& e) override;
	private:
		static application* s_instance;
	};


	application* create_application();
}
