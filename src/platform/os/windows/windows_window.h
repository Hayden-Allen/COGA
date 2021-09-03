#pragma once
#include "coga/window.h"

namespace coga
{
	/**
	 * Windows implementation of the window interface using GLFW
	 */
	class windows_window final : public window
	{
	public:
		windows_window(const window_constructor& data);
		COGA_DCM(windows_window);
	public:
		void* get_native_window() const override
		{
			return m_context->get_window();
		}
		void set_vsync(bool enabled) override
		{
			glfwSwapInterval((m_vsync = enabled) ? 1 : 0);
		}
		std::string open_file_dialog(const char* filters) const override
		{
			return file_dialog("Open File", filters, OFN_FILEMUSTEXIST | OFN_EXPLORER);
		}
		std::string open_multi_file_dialog(const char* filters) const override
		{
			return file_dialog("Open Files", filters, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER);
		}
		std::string save_file_dialog(const char* filters) const override
		{
			return file_dialog("Save File", filters, 0);
		}
	protected:
		std::string file_dialog(const char* name, const char* filters, uint32_t flags) const override;
	private:
		static bool s_glfw_init;
	private:
		// GLFW callback functions
		static void error_callback(int code, const char* desc);
		static void char_callback(GLFWwindow* window, uint32_t code);
		static void key_callback(GLFWwindow* window, int key, int scan, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void mouse_move_callback(GLFWwindow* window, double x, double y);
		static void mouse_scroll_callback(GLFWwindow* window, double x, double y);
		static void window_close_callback(GLFWwindow* window);
		static void window_focus_callback(GLFWwindow* window, int focused);
		static void window_move_callback(GLFWwindow* window, int x, int y);
		static void window_size_callback(GLFWwindow* window, int width, int height);
	};
}
