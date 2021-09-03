#pragma once
#include "pch.h"
#include "retained_buffer.h"

namespace coga::gl
{
	template<GLenum USAGE>
	class retained_vertex_buffer : public coga::gl::retained_buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::retained_vertex_buffer>
	{
	public:
		COGA_DM(retained_vertex_buffer);
		virtual ~retained_vertex_buffer()
		{
			COGA_CORE_TRACE("Delete RVB {}", this->m_id);
		}
	protected:
		retained_vertex_buffer(coga::gfx::retained_vertex_buffer::s_type* data, size_t count) :
			coga::gl::retained_buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::retained_vertex_buffer>(data, count)
		{
			COGA_CORE_TRACE("Create RVB {}", this->m_id);
		}
		retained_vertex_buffer(const retained_vertex_buffer& other, size_t count) :
			coga::gl::retained_buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::retained_vertex_buffer>(other, count)
		{
			COGA_CORE_TRACE("Create RVB {}", this->m_id);
		}
		retained_vertex_buffer(input_file& in) :
			coga::gl::retained_buffer<GL_ARRAY_BUFFER, USAGE, coga::gfx::retained_vertex_buffer>(in)
		{
			COGA_CORE_TRACE("Create RVB {}", this->m_id);
		}
	};



	class retained_static_vertex_buffer : public coga::gl::retained_vertex_buffer<GL_STATIC_DRAW>
	{
	public:
		retained_static_vertex_buffer(s_type* vertices, size_t count) :
			retained_vertex_buffer<GL_STATIC_DRAW>(vertices, count)
		{}
		retained_static_vertex_buffer(const retained_static_vertex_buffer& other, size_t count) :
			retained_vertex_buffer<GL_STATIC_DRAW>(other, count)
		{}
		retained_static_vertex_buffer(input_file& in) :
			retained_vertex_buffer<GL_STATIC_DRAW>(in)
		{}
		COGA_DCM(retained_static_vertex_buffer);
	};



	class retained_dynamic_vertex_buffer : public coga::gl::retained_vertex_buffer<GL_DYNAMIC_DRAW>
	{
	public:
		retained_dynamic_vertex_buffer(s_type* vertices, size_t count) :
			retained_vertex_buffer<GL_DYNAMIC_DRAW>(vertices, count)
		{}
		retained_dynamic_vertex_buffer(const retained_dynamic_vertex_buffer& other, size_t count) :
			retained_vertex_buffer<GL_DYNAMIC_DRAW>(other, count)
		{}
		retained_dynamic_vertex_buffer(input_file& in) :
			retained_vertex_buffer<GL_DYNAMIC_DRAW>(in)
		{}
		COGA_DCM(retained_dynamic_vertex_buffer);
	};
}
