#include "pch.h"
#include "windows_input.h"
#include "application.h"

namespace coga
{
	input* input::s_instance = new windows_input();



#define WIN COGA_CAST(GLFWwindow*, application::get().get_window().get_native_window())
	bool windows_input::key_pressed(int key) const
	{
		int state = glfwGetKey(WIN, key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool windows_input::mouse_pressed(int button) const
	{
		return glfwGetMouseButton(WIN, button) == GLFW_PRESS;
	}
	float windows_input::mouse_x() const
	{
		double x, y;
		glfwGetCursorPos(WIN, &x, &y);
		return COGA_CAST(float, x);
	}
	float windows_input::mouse_y() const
	{
		double x, y;
		glfwGetCursorPos(WIN, &x, &y);
		return COGA_CAST(float, y);
	}
#undef WIN
}
