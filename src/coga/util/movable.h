#pragma once
#include "pch.h"

namespace coga
{
	class movable
	{
	public:
		const glm::vec2& get_vel() const
		{
			return m_vel;
		}
		virtual void set_vel(const glm::vec2& vel)
		{
			m_vel = vel;
		}
	protected:
		glm::vec2 m_vel;
	protected:
		movable(const glm::vec2& v) :
			m_vel(v)
		{}
	};



	class bounded_movable : public movable
	{
	public:
		void set_vel(const glm::vec2& vel) override
		{
			m_vel = (vel.length() > m_speed ? (glm::normalize(vel) * m_speed) : vel);
		}
	protected:
		float m_speed;
	protected:
		bounded_movable(const glm::vec2& vel, float speed) :
			movable(vel),
			m_speed(speed)
		{}
	};
}
