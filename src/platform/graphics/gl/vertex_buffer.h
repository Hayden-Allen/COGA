#pragma once
#include "pch.h"
#include "buffer.h"

namespace coga::gl
{
	template<GLenum USAGE>
	class vertex_buffer : public coga::gl::buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::vertex_buffer>
	{
	protected:
		using s_type = coga::gl::buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::vertex_buffer>::s_type;
	public:
		COGA_DCM(vertex_buffer);
		virtual ~vertex_buffer()
		{
			COGA_CORE_TRACE("Delete VB {}", this->m_id);
		}
	protected:
		vertex_buffer(s_type* vertices, size_t count) :
			coga::gl::buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::vertex_buffer>(count)
		{
			coga::gl::buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::vertex_buffer>::write(vertices, count);
			COGA_CORE_TRACE("Create VB {}", this->m_id);
		}
		vertex_buffer(coga::input_file& in) :
			coga::gl::buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::vertex_buffer>(in)
		{}
	};



	class static_vertex_buffer : public coga::gl::vertex_buffer<GL_STATIC_DRAW>
	{
	public:
		static_vertex_buffer(s_type* vertices, size_t count) :
			vertex_buffer<GL_STATIC_DRAW>(vertices, count)
		{}
		static_vertex_buffer(coga::input_file& in) :
			vertex_buffer<GL_STATIC_DRAW>(in)
		{}
		COGA_DCM(static_vertex_buffer);
	};



	class dynamic_vertex_buffer : public coga::gl::vertex_buffer<GL_DYNAMIC_DRAW>
	{
	public:
		dynamic_vertex_buffer(s_type* vertices, size_t count) :
			vertex_buffer<GL_DYNAMIC_DRAW>(vertices, count)
		{}
		dynamic_vertex_buffer(coga::input_file& in) :
			vertex_buffer<GL_DYNAMIC_DRAW>(in)
		{}
		COGA_DCM(dynamic_vertex_buffer);
	};
}
