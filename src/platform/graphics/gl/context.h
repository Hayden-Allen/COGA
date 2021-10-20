#pragma once
#include "pch.h"
#include "coga/graphics/context.h"

struct GLFWwindow;

namespace coga::gl
{
	class context final : public coga::gfx::context
	{
	public:
		context(void* const host, uint32_t w, uint32_t h, const std::string& title, bool vsync);
		COGA_DCM(context);
		~context()
		{
			glfwDestroyWindow(get_window<GLFWwindow*>());
		}
	private:
		static bool s_initialized;
	};
}
