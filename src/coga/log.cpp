#include "pch.h"
#include "log.h"

namespace coga
{
	spdlog::logger* log::s_core = nullptr;
	spdlog::logger* log::s_client = nullptr;



	void log::init()
	{
		spdlog::set_pattern("%^[%T | %n]: %v%$");
		// returned pointers are std::shared_pointers, and will be deleted by spdlog automatically when the program terminates
		s_core = spdlog::stdout_color_mt("COGA").get();
		s_client = spdlog::stdout_color_mt("APP ").get();
		s_core->set_level(spdlog::level::trace);
		s_client->set_level(spdlog::level::trace);
	}
	spdlog::logger* const log::get_core()
	{
		return s_core;
	}
	spdlog::logger* const log::get_client()
	{
		return s_client;
	}
}
