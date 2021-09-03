#include "pch.h"
#include "layer_stack.h"
#include "log.h"

namespace coga
{
	layer_stack::~layer_stack()
	{
		for (s_type l : m_list)
			delete l;
	}



	void layer_stack::attach(s_type const layer)
	{
		if (m_list.size() != 0)
			m_list.insert(begin() + m_insert, layer);
		else
			m_list.push_back(layer);
		m_insert++;
		layer->on_attach();
	}
	void layer_stack::detach(s_type const layer)
	{
		detach_base(layer);
		m_insert--;
	}
	void layer_stack::attach_top(s_type const layer)
	{
		m_list.push_back(layer);
		layer->on_attach();
	}
	void layer_stack::detach_top(s_type const layer)
	{
		detach_base(layer);
	}



	void layer_stack::detach_base(s_type const layer)
	{
		const auto& it = std::find(begin(), end(), layer);
		COGA_CORE_ASSERT(it != m_list.end(), "Attempted to detach a layer that is not part of the layer_stack");
		m_list.erase(it);
		layer->on_detach();
	}
}
