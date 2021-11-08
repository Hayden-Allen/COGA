#pragma once
#include "pch.h"
#include "../vendor/glm/glm/glm.hpp"
#include "typed.h"

namespace coga
{
	/**
	 * An object with position
	 */
	template<typename T>
	class positional : public typed<T>
	{
	public:
		template<typename U = T>
		U get_x() const
		{
			return COGA_CAST(U, m_x);
		}
		template<typename U = T>
		U get_y() const
		{
			return COGA_CAST(U, m_y);
		}
	protected:
		T m_x, m_y;
	protected:
		positional(T x, T y) :
			m_x(x),
			m_y(y)
		{}
	};


	class vector_positional
	{
	public:
		const glm::vec2& get_pos() const
		{
			return m_pos;
		}
		void set_pos(const glm::vec2& pos)
		{
			m_pos = pos;
		}
	protected:
		glm::vec2 m_pos;
	protected:
		vector_positional(const glm::vec2& pos) :
			m_pos(pos)
		{}
	};
}
