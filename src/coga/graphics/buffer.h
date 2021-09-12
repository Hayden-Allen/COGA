#pragma once
#include "pch.h"
#include "render_object.h"
#include "coga/io/serializable.h"
#include "coga/util/functions.h"
#include "coga/util/typed.h"

namespace coga::gfx
{
	template<typename T>
	class buffer :
		public render_object,
		public typed<T>,
		public serializable
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
		virtual void save(output_file& out) const override
		{
			COGA_CORE_ASSERT(false, "Cannot save a coga::gfx::buffer");
		}
		virtual void load(input_file& in) override
		{
			// read data into local buffer, upload to GPU, delete local buffer
			m_count = in.ulong();
			T* data = new T[m_count];
			in.read(data, m_count);
			write(data, m_count);
			delete[] data;
		}
	protected:
		size_t m_count;
	protected:
		buffer(size_t count) :
			m_count(count)
		{}
	protected:
		// upload data to the GPU
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
