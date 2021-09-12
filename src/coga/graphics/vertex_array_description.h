#pragma once
#include "pch.h"
#include "vertex_buffer_element.h"
#include "coga/util/iterable.h"

namespace coga::gfx
{
	/**
	 * Describes the layout and sizes of the groups of data contained within a vertex array
	 */
	class vertex_array_description final : public iterable<std::vector<vertex_buffer_element>>
	{
	public:
		vertex_array_description(const std::initializer_list<vertex_buffer_element>& elements) :
			iterable<std::vector<vertex_buffer_element>>(elements),
			m_stride(0)
		{
			size_t offset = 0;
			for (vertex_buffer_element& element : m_list)
			{
				element.m_offset = offset;
				m_stride += element.m_size;
				offset += element.m_size;
			}
		}
		COGA_DCM(vertex_array_description);
	public:
		template<typename T = size_t>
		T get_stride() const
		{
			return COGA_CAST(T, m_stride);
		}
	protected:
		size_t m_stride;
	};
}
