#pragma once
#include "pch.h"
#include "app_event.h"
#include "event.h"
#include "key_event.h"
#include "mouse_event.h"
#include "window_event.h"

#define MAGE_BIND_EVENT_CALLBACK(x) std::bind(&x, this, std::placeholders::_1)

namespace coga
{
	/**
	 * An object that responds to events
	 */
	class event_handler
	{
	public:
		COGA_DCM(event_handler);
	public:
		// app
		virtual bool on_app_tick(app_tick_event& e) { return false; }
		virtual bool on_app_draw(app_draw_event& e) { return false; }
		virtual bool on_app_render(app_render_event& e) { return false; }
		// key
		virtual bool on_key_press(key_press_event& e) { return false; }
		virtual bool on_key_release(key_release_event& e) { return false; }
		virtual bool on_key_type(key_type_event& e) { return false; }
		// mouse
		virtual bool on_mouse_press(mouse_press_event& e) { return false; }
		virtual bool on_mouse_release(mouse_release_event& e) { return false; }
		virtual bool on_mouse_move(mouse_move_event& e) { return false; }
		virtual bool on_mouse_scroll(mouse_scroll_event& e) { return false; }
		// window
		virtual bool on_window_close(window_close_event& e) { return false; }
		virtual bool on_window_resize(window_resize_event& e) { return false; }
		virtual bool on_window_focus(window_focus_event& e) { return false; }
		virtual bool on_window_unfocus(window_unfocus_event& e) { return false; }
		virtual bool on_window_move(window_move_event& e) { return false; }
		virtual void on_event(event& e)
		{
			// app
			e.dispatch<app_tick_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_app_tick));
			e.dispatch<app_draw_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_app_draw));
			e.dispatch<app_render_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_app_render));
			// key
			e.dispatch<key_press_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_key_press));
			e.dispatch<key_release_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_key_release));
			e.dispatch<key_type_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_key_type));
			// mouse
			e.dispatch<mouse_press_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_mouse_press));
			e.dispatch<mouse_release_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_mouse_release));
			e.dispatch<mouse_move_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_mouse_move));
			e.dispatch<mouse_scroll_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_mouse_scroll));
			// window
			e.dispatch<window_close_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_window_close));
			e.dispatch<window_resize_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_window_resize));
			e.dispatch<window_focus_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_window_focus));
			e.dispatch<window_unfocus_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_window_unfocus));
			e.dispatch<window_move_event>(MAGE_BIND_EVENT_CALLBACK(event_handler::on_window_move));
		}
	protected:
		event_handler() {}
	};
}
