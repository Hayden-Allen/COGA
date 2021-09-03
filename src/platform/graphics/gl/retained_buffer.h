#pragma once
#include "pch.h"
#include "buffer.h"
#include "coga/graphics/retained_buffer.h"
#include "coga/util/functions.h"

namespace coga::gl
{
	template<GLenum TARGET, GLenum USAGE, typename T>
	class retained_buffer : public T
	{
	protected:
		using s_type = T::s_type;
	public:
		COGA_DM(retained_buffer);
		virtual ~retained_buffer()
		{
			glDeleteBuffers(1, &this->m_id);
		}
	public:
		void bind() const override
		{
			glBindBuffer(TARGET, this->m_id);
		}
		void unbind() const override
		{
			glBindBuffer(TARGET, 0);
		}
		void update(const s_type* const data, size_t count, size_t offset) const override
		{
			COGA_CORE_ASSERT((offset + count) <= this->m_count, "Retained buffer overflow, consider resizing");
			bind();
			glBufferSubData(TARGET, offset * sizeof(T::s_type), count * sizeof(T::s_type), data);
			unbind();
			arrcopy(count, data, this->m_data + offset);
		}
		void save(output_file& out) const override
		{
			T::save(out);
		}
		void load(input_file& in) override
		{
			T::load(in);
			write(this->m_data, this->m_count);
		}
		void resize(size_t count) override
		{
			bind();

			// create new data store and upload as much of existing data as possible
			glBufferData(TARGET, count * sizeof(T::s_type), nullptr, USAGE);
			glBufferSubData(TARGET, 0, glm::min(this->m_count, count) * sizeof(T::s_type), this->m_data);

			T::resize(count);

			unbind();
		}
	protected:
		retained_buffer(T::s_type* data, size_t count) :
			T(count)
		{
			glGenBuffers(1, &this->m_id);
			write(data, count);
		}
		retained_buffer(const retained_buffer& other, size_t count) :
			T(other, count)
		{
			glGenBuffers(1, &this->m_id);
		}
		retained_buffer(input_file& in) :
			T(0)
		{
			glGenBuffers(1, &this->m_id);
			load(in);
		}
	protected:
		void write(const s_type* const data, size_t count) const override
		{
			bind();
			glBufferData(TARGET, count * sizeof(T::s_type), data, USAGE);
			unbind();
			arrcopy(count, data, this->m_data);
		}
	};
}
