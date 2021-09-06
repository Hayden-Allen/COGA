#pragma once
#include "pch.h"
#include "coga/graphics/buffer.h"

namespace coga::gl
{
	template<GLenum TARGET, GLenum USAGE, typename T>
	class buffer : public T
	{
	protected:
		using s_type = T::s_type;
	public:
		COGA_DM(buffer);
		virtual ~buffer()
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
			bind();
			glBufferSubData(TARGET, offset, count * sizeof(T::s_type), data);
			unbind();
		}
		void save(output_file& out) const override
		{
			T::save(out);
		}
		void load(input_file& in) override
		{
			T::load(in);
		}
	protected:
		buffer(size_t count) :
			T(count)
		{
			glGenBuffers(1, &this->m_id);
		}
		buffer(coga::input_file& in) :
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
		}
	};
}
