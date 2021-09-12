#pragma once
#include "pch.h"
#include "buffer.h"
#include "coga/io/serializable.h"
#include "coga/util/functions.h"

namespace coga::gfx
{
	/**
	 * A buffer that exists both on the GPU and in RAM.
	 */
	template<typename T>
	class retained_buffer :
		public T
	{
	public:
		virtual ~retained_buffer()
		{
			delete m_data;
		}
	public:
		virtual void save(output_file& out) const override
		{
			out.ulong(this->m_count);
			out.write(m_data, this->m_count);
		}
		virtual void load(input_file& in) override
		{
			this->m_count = in.ulong();
			m_data = new T::s_type[this->m_count];
			in.read(m_data, this->m_count);
		}
		virtual void resize(size_t count)
		{
			auto data = new T::s_type[count];
			// grow
			if (count > this->m_count)
			{
				// copy existing
				arrcopy(this->m_count, m_data, data);
				// set new to 0
				arrset(count - this->m_count, data, COGA_CAST(T::s_type, 0), this->m_count);
			}
			// shrink
			if (count < this->m_count)
				arrcopy(count, m_data, data);

			m_data = data;
			delete[] data;
			this->m_count = count;
		}
	protected:
		T::s_type* m_data;
	protected:
		retained_buffer(T::s_type* const data, size_t count) :
			T(count),
			m_data(data)
		{}
	};



	class retained_index_buffer : public retained_buffer<index_buffer>
	{
	protected:
		retained_index_buffer(size_t count) :
			retained_buffer<index_buffer>(new s_type[count], count)
		{}
		retained_index_buffer(s_type* const data, size_t count) :
			retained_buffer<index_buffer>(data, count)
		{}
		retained_index_buffer(const retained_index_buffer& other, size_t count) :
			retained_buffer<index_buffer>(new s_type[count], count)
		{
			arrcopy(other.get_count(), other.m_data, m_data);
			arrset(count - other.get_count(), m_data, COGA_CAST(s_type, 0), other.get_count());
		}
	};



	class retained_vertex_buffer : public retained_buffer<vertex_buffer>
	{
	protected:
		retained_vertex_buffer(size_t count) :
			retained_buffer<vertex_buffer>(new s_type[count], count)
		{}
		retained_vertex_buffer(s_type* const data, size_t count) :
			retained_buffer<vertex_buffer>(data, count)
		{}
		retained_vertex_buffer(const retained_vertex_buffer& other, size_t count) :
			retained_buffer<vertex_buffer>(new s_type[count], count)
		{
			arrcopy(other.get_count(), other.m_data, m_data);
			arrset(count - other.get_count(), m_data, COGA_CAST(s_type, 0), other.get_count());
		}
	};
}
