#pragma once
#include "pch.h"
#include "retained_buffer.h"
#include "vertex_buffer.h"
#include "coga/graphics/vertex_array.h"

namespace coga::gl
{
	template<GLenum USAGE>
	class vertex_array : public coga::gfx::vertex_array
	{
	public:
		COGA_DCM(vertex_array);
		~vertex_array()
		{
			COGA_CORE_TRACE("Delete VA {}", m_id);
		}
	public:
		void bind() const override
		{
			glBindVertexArray(this->m_id);
		}
		void unbind() const override
		{
			glBindVertexArray(0);
		}
	protected:
		vertex_array(coga::gl::vertex_buffer<USAGE>* const buffer, const s_desc& desc) :
			coga::gfx::vertex_array(buffer, desc.get_stride())
		{
			init(desc);
		}
		vertex_array(coga::gl::retained_vertex_buffer<USAGE>* const buffer, const s_desc& desc) :
			coga::gfx::vertex_array(buffer, desc.get_stride())
		{
			init(desc);
		}
	private:
		void init(const s_desc& desc)
		{
			glGenVertexArrays(1, &this->m_id);

			bind();
			this->m_buffer->bind();

			uint32_t i = 0;
			for (auto& element : desc)
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.get_count<GLint>(), get_shader_type_base(element.get_type()), GL_FALSE, desc.get_stride<GLsizei>(), (const void*)element.get_offset());
				i++;
			}

			COGA_CORE_TRACE("Create VA {}", m_id);
			unbind();
		}
	};



	class static_vertex_array : public coga::gl::vertex_array<GL_STATIC_DRAW>
	{
	public:
		static_vertex_array(coga::gl::static_vertex_buffer* const buffer, const s_desc& desc) : coga::gl::vertex_array<GL_STATIC_DRAW>(buffer, desc)
		{}
		static_vertex_array(coga::gl::retained_static_vertex_buffer* const buffer, const s_desc & desc) : coga::gl::vertex_array<GL_STATIC_DRAW>(buffer, desc)
		{}
		COGA_DCM(static_vertex_array);
	};



	class dynamic_vertex_array : public coga::gl::vertex_array<GL_DYNAMIC_DRAW>
	{
	public:
		dynamic_vertex_array(coga::gl::dynamic_vertex_buffer* const buffer, const s_desc& desc) : coga::gl::vertex_array<GL_DYNAMIC_DRAW>(buffer, desc)
		{}
		dynamic_vertex_array(coga::gl::retained_dynamic_vertex_buffer* const buffer, const s_desc & desc) : coga::gl::vertex_array<GL_DYNAMIC_DRAW>(buffer, desc)
		{}
		COGA_DCM(dynamic_vertex_array);
	};
}
