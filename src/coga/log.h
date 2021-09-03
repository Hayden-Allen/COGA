#pragma once
#include "pch.h"

namespace coga
{
	class log final
	{
	public:
		static void init();
		static spdlog::logger* const get_core();
		static spdlog::logger* const get_client();
	private:
		static spdlog::logger* s_core;
		static spdlog::logger* s_client;
	};
}



#ifndef COGA_DIST
	#define COGA_CORE_TRACE(...) ::coga::log::get_core()->trace(__VA_ARGS__)
	#define COGA_CORE_INFO(...)  ::coga::log::get_core()->info(__VA_ARGS__)
	#define COGA_CORE_WARN(...)  ::coga::log::get_core()->warn(__VA_ARGS__)
	#define COGA_CORE_ERROR(...) ::coga::log::get_core()->error(__VA_ARGS__)
	#define COGA_TRACE(...)		 ::coga::log::get_client()->trace(__VA_ARGS__)
	#define COGA_INFO(...)		 ::coga::log::get_client()->info(__VA_ARGS__)
	#define COGA_WARN(...)		 ::coga::log::get_client()->warn(__VA_ARGS__)
	#define COGA_ERROR(...)		 ::coga::log::get_client()->error(__VA_ARGS__)
#else
	#define COGA_CORE_TRACE(...)
	#define COGA_CORE_INFO(...) 
	#define COGA_CORE_WARN(...) 
	#define COGA_CORE_ERROR(...)
	#define COGA_TRACE(...)
	#define COGA_INFO(...) 
	#define COGA_WARN(...) 
	#define COGA_ERROR(...)
#endif



#ifndef COGA_DIST
	#define COGA_CORE_ASSERT(x, ...) if(!(x)) { COGA_CORE_ERROR(__VA_ARGS__); __debugbreak(); }
	#define COGA_ASSERT(x, ...) if(!(x)) { COGA_ERROR(__VA_ARGS__); __debugbreak(); }
#else
	#define COGA_CORE_ASSERT(x, ...)
	#define COGA_ASSERT(x, ...)
#endif
