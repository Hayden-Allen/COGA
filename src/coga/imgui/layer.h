#pragma once
#include "pch.h"
#include "coga/layer/layer.h"

namespace coga::imgui
{
	/**
	 * Interface for platform-specific imgui implementations
	 */
	class layer : public coga::layer
	{
	public:
		COGA_DCM(layer);
		virtual ~layer();
	public:
		bool on_app_tick(app_tick_event& e) final override;
		bool on_app_render(app_render_event& e) final override;
		virtual bool on_key_press(key_press_event& e) override;
		virtual bool on_key_release(key_release_event& e) override;
		// overriding both this and on_key_press results in characters being typed twice
		// virtual bool on_key_type(key_type_event& e) override;
		virtual bool on_mouse_press(mouse_press_event& e) override;
		virtual bool on_mouse_release(mouse_release_event& e) override;
		virtual bool on_mouse_move(mouse_move_event& e) override;
		virtual bool on_mouse_scroll(mouse_scroll_event& e) override;
		virtual bool on_window_resize(window_resize_event& e) override;
		virtual void on_key_base(key_event& e, bool pressed);
	protected:
		static uint32_t s_instance_count;
		uint32_t m_instance_id;
	protected:
	#ifndef MAGE_DIST
		layer(const std::string& name = "imgui");
	#else
		layer();
	#endif
	protected:
		virtual void app_tick(app_tick_event& e) const = 0;
		virtual void app_render(app_render_event& e) const = 0;
	private:
		constexpr static int s_imgui_min_charcode = 0, s_imgui_max_charcode = 0xffff;
	private:
		static void init();
		static void end();
	};
}
