#pragma once
#include "pch.h"
#include "typed.h"

namespace coga
{
	template<typename T, typename HANDLE, size_t COUNT>
	class bank : public typed<T>
	{
	public:
		typedef HANDLE handle;
	public:
		constexpr static size_t s_invalid = 0, s_placeholder = 1, s_first = 2;
	public:
		COGA_DCM(bank);
		virtual ~bank() {}
	public:
		static bool is_valid(HANDLE h)
		{
			return h != s_invalid && h != s_placeholder;
		}
		handle add(T* t)
		{
			COGA_CORE_ASSERT(m_next < COUNT, "Bank is full ({}/{})", COUNT, COUNT);
			handle ret = COGA_CAST(handle, get_next());
			m_bank[ret] = t;
			m_next += (ret == m_next);
			return ret;
		}
		void remove(const handle& h)
		{
			COGA_CORE_ASSERT(is_valid(h), "Cannot remove an invalid bank handle");
			// don't want to "remove" the same item multiple times
			if (m_bank[h])
			{
				delete m_bank[h];
				m_bank[h] = nullptr;
				m_openings.push_back(COGA_CAST(size_t, h));
			}
		}
		T* const get(HANDLE h)
		{
			return m_bank[COGA_CAST(size_t, h)];
		}
		const T* const get(HANDLE h) const
		{
			return m_bank[COGA_CAST(size_t, h)];
		}
		const size_t get_size() const
		{
			// account for invalid
			return m_next - s_first;
		}
		const size_t get_last() const
		{
			return m_next;
		}
	protected:
		size_t m_next;
		std::vector<size_t> m_openings;
		T* m_bank[COUNT];
	protected:
		bank() :
			m_next(s_first),
			m_bank{ nullptr }
		{}
	private:
		size_t get_next()
		{
			size_t n = m_next;
			if (!m_openings.empty())
			{
				n = m_openings.back();
				m_openings.pop_back();
			}
			return n;
		}
	};



#define COGA_BANK_DTOR(B) \
	B::~B() { for(size_t i = 0; i < this->m_next; i++) delete this->m_bank[i]; }
	/**
	 * T must also implement the serializable interface
	 */
	template<typename T, typename HANDLE, size_t COUNT>
	class serializable_bank :
		public bank<T, HANDLE, COUNT>,
		public serializable
	{
	public:
		COGA_DCM(serializable_bank);
	public:
		void save(output_file& out) const final override
		{
			out.ulong(this->get_last());
			for (size_t i = this->s_first; i < this->get_last(); i++)
				this->m_bank[i]->save(out);
		}
		void load(input_file& in) final override
		{
			this->m_next = in.ulong();
			for (size_t i = this->s_first; i < this->m_next; i++)
				this->m_bank[i] = new T(in);
		}
	protected:
		serializable_bank() {}
		serializable_bank(input_file& in)
		{
			load(in);
		}
	};
}
