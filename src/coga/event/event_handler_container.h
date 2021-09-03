#pragma once
#include "log.h"
#include "event_handler.h"
#include "coga/util/iterable.h"

namespace coga
{
	class event_handler_container : public iterable<std::vector<event_handler*>>
	{
	public:
		COGA_DCM(event_handler_container);
		virtual ~event_handler_container() {}
	public:
		void dispatch(event& e)
		{
			for (event_handler* const eh : m_list)
				eh->on_event(e);
		}
		void add(event_handler* const e)
		{
			m_list.emplace_back(e);
		}
		void remove(event_handler* const e)
		{
			const auto& it = std::find(begin(), end(), e);
			COGA_CORE_ASSERT(it != m_list.end(), "Attempted to remove an event_handler from an event_handler_container that does not contain it");
			m_list.erase(it);
		}
	protected:
		event_handler_container() {}
	};
}
