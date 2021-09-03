#pragma once
#include "core.h"

// used for convenience when implementing event classes
#define MAGE_EVENT_TYPE(type) \
	virtual const char* get_name() const override { return #type; } \
	virtual event_type get_type() const override { return type; } \
	static event_type get_static_type() { return type; }
#define MAGE_EVENT_CATEGORIES(categories) \
	virtual uint32_t get_categories() const override { return categories; }

namespace coga
{
	enum class event_type
	{
		none = 0,
		app_tick, app_draw, app_render,
		key_press, key_release, key_type,
		mouse_press, mouse_release, mouse_move, mouse_scroll,
		window_close, window_resize, window_focus, window_unfocus, window_move
	};
	// these need to behave like ints, so they can't be an enum class. I still want them scoped though
	namespace event_category
	{
		enum ec
		{
			none = 0,
			input = COGA_BIT(0),
			keyboard = COGA_BIT(1),
			mouse = COGA_BIT(2),
			mouse_button = COGA_BIT(3),
			app = COGA_BIT(4),
			window = COGA_BIT(5)
		};
	}



	class event
	{
		template<typename T>
		using dispatch_fn = std::function<bool(T&)>;
	public:
		COGA_DCM(event);
	public:
		virtual event_type get_type() const = 0;
		virtual uint32_t get_categories() const = 0;
		// these will only be used to print debug messages
	#ifndef MAGE_DIST
		virtual const char* get_name() const = 0;
		virtual std::string to_string() const
		{
			return get_name();
		}
	#endif
		// whether or not this event is in the given category
		bool is(event_category::ec c)
		{
			return get_categories() & COGA_CAST(uint32_t, c);
		}
		bool was_handled() const
		{
			return m_handled;
		}
		// if this event's type matches the given type, call the given function with it
		template<typename T>
		bool dispatch(dispatch_fn<T> fn)
		{
			if (get_type() == T::get_static_type())
			{
				m_handled = fn(COGA_PUN(T, *this));
				return true;
			}
			return false;
		}
	protected:
		bool m_handled;
	protected:
		event() : m_handled(false) {}
	};
}
