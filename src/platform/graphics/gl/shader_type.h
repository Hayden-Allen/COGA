#pragma once
#include "pch.h"
#include "coga/graphics/shader_type.h"

namespace coga::gfx
{
	template<typename T>
	static GLenum get_shader_type()
	{
		COGA_CORE_ASSERT(false, "Invalid GL shader type");
		return GL_NONE;
	}
	template<>
	static GLenum get_shader_type<float>()
	{
		return GL_FLOAT;
	}
	template<>
	static GLenum get_shader_type<uint32_t>()
	{
		return GL_UNSIGNED_INT;
	}



	static GLenum shader_type_base[] =
	{
		GL_NONE,
		GL_BOOL,
		GL_INT, GL_INT, GL_INT, GL_INT,
		GL_UNSIGNED_INT, GL_UNSIGNED_INT, GL_UNSIGNED_INT, GL_UNSIGNED_INT,
		GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT,
		GL_FLOAT, GL_FLOAT
	};
	static GLenum get_shader_type_base(shader_type t)
	{
		COGA_CORE_ASSERT(t != shader_type::none, "Invalid GL shader type");
		return shader_type_base[COGA_CAST(size_t, t)];
	}
}
