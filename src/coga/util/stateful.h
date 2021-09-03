#pragma once
#include "pch.h"

namespace coga
{
	template<typename K, typename V>
	class stateful
	{
	public:
		stateful(const std::unordered_map<K, V>& states, const K& state) :
			m_states(states),
			m_current_state(state)
		{
			validate();
		}
		COGA_DCM(stateful);
	public:
		const V& get_state() const
		{
			return m_states[m_current_state];
		}
		V& get_state()
		{
			return m_states[m_current_state];
		}
		void set_state(const K& state)
		{
			m_current_state = state;
			validate();
		}
	protected:
		std::unordered_map<K, V> m_states;
		K m_current_state;
	private:
		void validate() const
		{
			COGA_CORE_ASSERT(m_states.contains(m_current_state), "Invalid state {}", m_current_state);
		}
	};
}
