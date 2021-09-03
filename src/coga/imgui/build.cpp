#include "pch.h"
#ifdef COGA_PLATFORM_WINDOWS
	#define IMGUI_IMPL_OPENGL_LOADER_GLAD
	#undef _WIN32
	#include <backends/imgui_impl_opengl3.cpp>
	#include <backends/imgui_impl_glfw.cpp>
#endif