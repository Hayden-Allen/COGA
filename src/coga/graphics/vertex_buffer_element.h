#pragma once
#include "pch.h"
#include "shader_type.h"

namespace coga::gfx
{
	class vertex_buffer_element final
	{
		friend class vertex_array_description;
	public:
		vertex_buffer_element(shader_type t) :
			m_type(t),
			m_count(get_shader_type_element_count(t)),
			m_size(m_count * get_shader_type_base_size(t)),
			m_offset(0)
		{}
		vertex_buffer_element(const vertex_buffer_element & other) :
			m_type(other.m_type),
			m_count(other.m_count),
			m_size(other.m_size),
			m_offset(other.m_offset)
		{}
		COGA_DM(vertex_buffer_element);
	public:
		shader_type get_type() const
		{
			return m_type;
		}
		template<typename T = size_t>
		T get_count() const
		{
			return COGA_CAST(T, m_count);
		}
		template<typename T = size_t>
		T get_offset() const
		{
			return COGA_CAST(T, m_offset);
		}
	private:
		shader_type m_type;
		size_t m_count, m_size, m_offset;
	};
}
