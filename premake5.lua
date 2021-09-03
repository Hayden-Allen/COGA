--[[
workspace "COGA"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
]]--

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}-%{cfg.system}"

include "vendor/GLFW"
include "vendor/glad"
include "vendor/imgui"

project "COGA"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	flags "MultiProcessorCompile"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir)

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.c",
		"src/**.cpp"
	}

	includedirs
	{
		"src/",
		"src/coga/",
		"vendor/spdlog/include/",
		"vendor/GLFW/include/",
		"vendor/glad/include/",
		"vendor/imgui/",
		"vendor/glm/"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad",
		"imgui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"COGA_PLATFORM_WINDOWS",
			"COGA_RENDER_API_GL",
			"COGA_RAN=coga::gl",
			"COGA_BUILD_LIB",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "COGA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "COGA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "COGA_DIST"
		runtime "Release"
		optimize "on"