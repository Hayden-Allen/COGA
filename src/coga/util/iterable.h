#pragma once
#include "pch.h"
#include "typed.h"

namespace coga
{
	template<typename T>
	class iterable : public typed<typename T::value_type>
	{
	public:
		COGA_DCM(iterable);
	public:
		T::iterator begin()
		{
			return m_list.begin();
		}
		T::iterator end()
		{
			return m_list.end();
		}
		T::const_iterator begin() const
		{
			return m_list.begin();
		}
		T::const_iterator end() const
		{
			return m_list.end();
		}
	protected:
		typedef T s_list;
	protected:
		T m_list;
	protected:
		iterable() {}
		iterable(const T& list) :
			m_list(list)
		{}
	};
}
