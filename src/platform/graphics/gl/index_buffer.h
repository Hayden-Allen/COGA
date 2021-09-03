#pragma once
#include "pch.h"
#include "buffer.h"

namespace coga::gl
{
	template<GLenum USAGE>
	class index_buffer : public coga::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, coga::gfx::index_buffer>
	{
	protected:
		using s_type = coga::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, coga::gfx::index_buffer>::s_type;
	public:
		COGA_DCM(index_buffer);
		virtual ~index_buffer()
		{
			COGA_CORE_TRACE("Delete IB {}", this->m_id);
		}
	protected:
		index_buffer(size_t count) :
			coga::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, coga::gfx::index_buffer>(count)
		{
			COGA_CORE_TRACE("Create IB {}", this->m_id);
		}
		index_buffer(s_type* indices, size_t count) :
			coga::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, coga::gfx::index_buffer>(count)
		{
			coga::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, coga::gfx::index_buffer>::write(indices, count);
			COGA_CORE_TRACE("Create IB {}", this->m_id);
		}
	};



	class static_index_buffer : public coga::gl::index_buffer<GL_STATIC_DRAW>
	{
	public:
		static_index_buffer(size_t count) :
			index_buffer<GL_STATIC_DRAW>(count)
		{}
		static_index_buffer(s_type* indices, size_t count) :
			index_buffer<GL_STATIC_DRAW>(indices, count)
		{}
		COGA_DCM(static_index_buffer);
	};



	class dynamic_index_buffer : public coga::gl::index_buffer<GL_DYNAMIC_DRAW>
	{
	public:
		dynamic_index_buffer(size_t count) :
			index_buffer<GL_DYNAMIC_DRAW>(count)
		{}
		dynamic_index_buffer(s_type* indices, size_t count) :
			index_buffer<GL_DYNAMIC_DRAW>(indices, count)
		{}
		COGA_DCM(dynamic_index_buffer);
	};
}
