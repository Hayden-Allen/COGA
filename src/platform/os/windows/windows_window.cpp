#include "pch.h"
#include "windows_window.h"
#include "coga/event/key_event.h"
#include "coga/event/mouse_event.h"
#include "coga/event/window_event.h"
#include "coga/graphics/renderer.h"
#include "platform/graphics/gl/context.h"

namespace coga
{
	constexpr char window::get_multi_file_separator_token()
	{
		return '|';
	}
	/**
	 * Windows implementation; called by application()
	 */
	window* window::create(const window_constructor& data)
	{
		return new windows_window(data);
	}



	bool windows_window::s_glfw_init = false;



	windows_window::windows_window(const window_constructor& data) :
		window(data)
	{
		// initialize graphics context
		m_context = coga::gfx::context::create(this, m_w, m_h, m_title, data.vsync);

		// window settings
		set_vsync(m_vsync);
		gfx::renderer::set_clear_color(m_clear);

		GLFWwindow* const win = m_context->get_window<GLFWwindow*>();
		// callbacks
		glfwSetErrorCallback(error_callback);
		glfwSetCharCallback(win, char_callback);
		glfwSetKeyCallback(win, key_callback);
		glfwSetMouseButtonCallback(win, mouse_button_callback);
		glfwSetCursorPosCallback(win, mouse_move_callback);
		glfwSetScrollCallback(win, mouse_scroll_callback);
		glfwSetWindowCloseCallback(win, window_close_callback);
		glfwSetWindowFocusCallback(win, window_focus_callback);
		glfwSetWindowPosCallback(win, window_move_callback);
		glfwSetWindowSizeCallback(win, window_size_callback);
	}



	std::string windows_window::file_dialog(const char* name, const char* filters, uint32_t flags) const
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window(COGA_CAST(GLFWwindow*, get_native_window()));
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filters;
		ofn.nFilterIndex = 1;
		ofn.lpstrTitle = name;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | flags;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			for (size_t i = 0; !(ofn.lpstrFile[i] == 0 && ofn.lpstrFile[i + 1] == 0); i++)
				if (ofn.lpstrFile[i] == 0)
					ofn.lpstrFile[i] = '|';
			return ofn.lpstrFile;
		}
		return std::string();
	}



	/**
	 * GLFW callbacks
	 */
#define WIN COGA_CAST(windows_window*, glfwGetWindowUserPointer(window))
	void windows_window::error_callback(int code, const char* desc)
	{
		COGA_CORE_ERROR("[GLFW Error {}]: {}", code, desc);
	}
	void windows_window::char_callback(GLFWwindow* window, uint32_t code)
	{
		key_type_event e(COGA_CAST(int, code));
		WIN->invoke(e);
	}
	void windows_window::key_callback(GLFWwindow* window, int key, int scan, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			key_press_event e(key, action == GLFW_REPEAT);
			WIN->invoke(e);
		}
		else if (action == GLFW_RELEASE)
		{
			key_release_event e(key);
			WIN->invoke(e);
		}
	}
	void windows_window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			mouse_press_event e(button);
			WIN->invoke(e);
		}
		else if (action == GLFW_RELEASE)
		{
			mouse_release_event e(button);
			WIN->invoke(e);
		}
	}
	void windows_window::mouse_move_callback(GLFWwindow* window, double x, double y)
	{
		mouse_move_event e(COGA_CAST(float, x), COGA_CAST(float, y));
		WIN->invoke(e);
	}
	void windows_window::mouse_scroll_callback(GLFWwindow* window, double x, double y)
	{
		mouse_scroll_event e(COGA_CAST(float, x), COGA_CAST(float, y));
		WIN->invoke(e);
	}
	void windows_window::window_close_callback(GLFWwindow* window)
	{
		window_close_event e;
		WIN->invoke(e);
	}
	void windows_window::window_focus_callback(GLFWwindow* window, int focused)
	{
		if (focused)
		{
			window_focus_event e;
			WIN->invoke(e);
		}
		else
		{
			window_unfocus_event e;
			WIN->invoke(e);
		}
	}
	void windows_window::window_move_callback(GLFWwindow* window, int x, int y)
	{
		WIN->m_x = COGA_CAST(positional::s_type, x);
		WIN->m_y = COGA_CAST(positional::s_type, y);

		window_move_event e(x, y);
		WIN->invoke(e);
	}
	void windows_window::window_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		WIN->m_w = COGA_CAST(dimensional::s_type, width);
		WIN->m_h = COGA_CAST(dimensional::s_type, height);

		window_resize_event e(width, height);
		WIN->invoke(e);
	}
#undef WIN
}
