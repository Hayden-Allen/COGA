#pragma once
#include "pch.h"
#include "typed.h"
#include "functions.h"

namespace coga
{
	template<typename T, typename RETURN = size_t, typename ADD = const T&, typename REMOVE = const RETURN&>
	class indexed_list : public typed<T>
	{
	public:
		typedef RETURN handle;

		indexed_list(size_t count, const T& placeholder) :
			m_count(count),
			m_next(0),
			m_list(new T[count]),
			m_placeholder(placeholder)
		{
			arrset(count, m_list, placeholder);
			m_openings.reserve(count);
		}
		COGA_DCM(indexed_list);
		virtual ~indexed_list()
		{
			delete[] m_list;
		}
	public:
		virtual RETURN add(ADD t) = 0;
		virtual void remove(REMOVE t) = 0;
		const T& operator[](size_t i) const
		{
			return m_list[i];
		}
		T& operator[](size_t i)
		{
			return m_list[i];
		}
		size_t get_capacity() const
		{
			return m_count;
		}
		size_t get_size() const
		{
			return m_next - m_openings.size();
		}
		size_t get_next() const
		{
			return m_next;
		}
		bool is_empty() const
		{
			return m_openings.size() == m_next;
		}
		bool is_full() const
		{
			return m_next == m_count && m_openings.empty();
		}
		template<typename T>
		void for_each(T fn) const
		{
			for (size_t i = 0; i < get_next(); i++)
				if (is_valid(i))
					fn(m_list[i]);
		}
		template<typename T>
		void for_each(T fn)
		{
			for (size_t i = 0; i < get_next(); i++)
				if (is_valid(i))
					fn(m_list[i]);
		}
	protected:
		size_t m_count, m_next;
		std::vector<size_t> m_openings;
		T* m_list, m_placeholder;
	protected:
		size_t add_base(ADD t)
		{
			COGA_CORE_ASSERT(!is_full(), "indexed_list is full");
			const size_t i = next_index();
			m_list[i] = t;
			m_next += (i == m_next);
			return i;
		}
		void remove_base(size_t i)
		{
			COGA_CORE_ASSERT(i < m_count, "Invalid indexed_list index {}", i);

			// only remove if something's actually there
			if (m_list[i] != m_placeholder)
			{
				m_list[i] = m_placeholder;
				m_openings.push_back(i);
			}
		}
		size_t next_index()
		{
			size_t i = m_next;
			if (!m_openings.empty())
			{
				i = m_openings.back();
				m_openings.pop_back();
			}
			return i;
		}
		bool is_valid(size_t i) const
		{
			return i < m_count && m_list[i] != m_placeholder;
		}
	};
}
