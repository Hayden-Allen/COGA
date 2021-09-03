#pragma once
#include "pch.h"
#include "render_object.h"
#include "coga/util/typed.h"

namespace coga::gfx
{
	template<typename T>
	class buffer :
		public render_object,
		public typed<T>
	{
	public:
		COGA_DCM(buffer);
	public:
		virtual void update(const T* const data, size_t count, size_t offset) const = 0;
		template<typename U = size_t>
		U get_count() const
		{
			return COGA_CAST(U, m_count);
		}
	protected:
		size_t m_count;
	protected:
		buffer(size_t count) :
			m_count(count)
		{}
	protected:
		virtual void write(const T* const data, size_t count) const = 0;
	};



	class index_buffer : public buffer<uint32_t>
	{
	public:
		virtual ~index_buffer() {}
	protected:
		index_buffer(size_t count) :
			buffer<s_type>(count)
		{}
	};



	class vertex_buffer : public buffer<float>
	{
	public:
		virtual ~vertex_buffer() {}
	protected:
		vertex_buffer(size_t count) :
			buffer<s_type>(count)
		{}
	};
}
