#pragma once
#include "pch.h"
#include "shader_program.h"
#include "vertex_array.h"
#include "util/color.h"
#include "window.h"

namespace coga::gfx
{
	class renderer
	{
	public:
		static void set_clear_color(const color<float>& color);
		static void clear();
		static void draw(const index_buffer* const indices, const vertex_array* const vertices);
		static void draw(const shader_program* const shader, const index_buffer* const indices, const vertex_array* const vertices);
		static void render(const window* const window);
	protected:
		renderer() {}
	};
}
