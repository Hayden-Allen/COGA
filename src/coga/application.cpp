#include "pch.h"
#include "application.h"

namespace coga
{
	application* application::s_instance = nullptr;



	void application::run()
	{
		while (m_running)
		{
			const float time = COGA_CAST(float, glfwGetTime() * 1000.f);
			m_delta_time = time - m_time;
			m_time = time;

			app_tick_event tick(m_time, m_delta_time);
			app_draw_event draw(m_time, m_delta_time);
			app_render_event render(m_time, m_delta_time);

			// clear screen
			gfx::renderer::clear();

			// clear layers
			for (auto layer : m_layer_stack)
				layer->on_event(tick);
			// draw layers
			for (auto layer : m_layer_stack)
				layer->on_event(draw);
			// render layers
			for (auto layer : m_layer_stack)
				layer->on_event(render);

			// render screen
			gfx::renderer::render(m_window);
		}
	}



	application::application(const window_constructor& data) :
		m_running(true),
		m_time(0.f),
		m_delta_time(0.f),
		m_window(nullptr)
	{
		COGA_CORE_ASSERT(!s_instance, "Cannot create multiple applications");
		s_instance = this;

		m_window = window::create(data);
		m_window->set_event_callback(MAGE_BIND_EVENT_CALLBACK(application::on_event));
	}
	void application::on_event(coga::event& e)
	{
		event_handler::on_event(e);
		// traverse from the top down
		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin() && !e.was_handled();)
			(*--it)->on_event(e);
	}
}
