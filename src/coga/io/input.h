#pragma once
#include "pch.h"
#include "input_key.h"
#include "input_mouse.h"
#include "coga/log.h"
#include <glm/glm.hpp>

namespace coga
{
	/**
	 * Interface for polling various input devices
	 */
	class input
	{
	public:
		COGA_DCM(input);
	public:
		bool is_key_pressed(int key) const { return key_pressed(key); }
		bool are_keys_pressed(const std::vector<key::code>& keys) const
		{
			for (key::code key : keys)
				if (!is_key_pressed(key))
					return false;
			return true;
		}
		bool is_mouse_left() const { return is_mouse_pressed(mouse::left); }
		bool is_mouse_right() const { return is_mouse_pressed(mouse::right); }
		bool is_mouse_pressed(int button) const { return mouse_pressed(button); }
		float get_mouse_x() const { return mouse_x(); }
		float get_mouse_y() const { return mouse_y(); }
		glm::vec2 get_mouse_pos() const { return { mouse_x(), mouse_y() }; }
		static const input& get() { return *s_instance; }
	protected:
		input()
		{
			s_instance = this;
		}
	protected:
		virtual bool key_pressed(int key) const = 0;
		virtual bool mouse_pressed(int button) const = 0;
		virtual float mouse_x() const = 0;
		virtual float mouse_y() const = 0;
	private:
		static input* s_instance;
	};
}
