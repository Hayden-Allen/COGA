#pragma once
#include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "coga/event/event_handler_container.h"
#include "coga/layer/layer.h"
#include "coga/util/typed.h"

namespace coga::gfx
{
	template<typename T>
	class camera : 
		public event_handler,
		public typed<T>
	{
	public:
		typedef typed<T>::s_type s_type;
	public:
		COGA_DCM(camera);
		virtual ~camera() {}
	public:
		virtual const glm::mat4& get_projection() const
		{
			return m_projection;
		}
		virtual const glm::mat4& get_view() const
		{
			return m_view;
		}
		virtual const glm::mat4& get_view_projection() const
		{
			return m_view_projection;
		}
		virtual const glm::vec3& get_pos() const
		{
			return m_pos;
		}
		virtual const s_type& get_rotation() const
		{
			return m_rotation;
		}
		virtual void set_pos(const glm::vec3& pos)
		{
			m_pos = pos;
			update();
		}
		virtual void set_rotation(const s_type& rotation)
		{
			m_rotation = rotation;
			update();
		}
	protected:
		glm::mat4 m_projection, m_view, m_view_projection;
		glm::vec3 m_pos;
		s_type m_rotation;
	protected:
		camera(event_handler_container& c, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& pos, const s_type& rotation) :
			m_projection(projection),
			m_view(view),
			m_view_projection(view * projection),
			m_pos(pos),
			m_rotation(rotation)
		{
			c.add(this);
		}
	protected:
		virtual void update() = 0;
	};



	class orthographic_camera : public camera<float>, public dimensional<float>
	{
	public:
		typedef camera::s_type s_type;
	public:
		COGA_DCM(orthographic_camera);
		virtual ~orthographic_camera() {}
	public:
		float get_zoom() const
		{
			return m_zoom;
		}
		void set_zoom(float zoom)
		{
			if (m_zoom != zoom)
			{
				m_zoom = zoom;
				m_projection = compute_projection(m_w, m_h);
				update();
			}
		}
		void set_size(float w, float h)
		{
			if (m_w != w || m_h != h)
			{
				m_projection = compute_projection(m_w = w, m_h = h);
				update();
			}
		}
	protected:
		float m_zoom;
	protected:
		orthographic_camera(event_handler_container& c, float width, float height, const glm::vec3& pos, s_type rotation, float zoom) :
			camera<float>(c, compute_initial_projection(width, height, zoom), glm::mat4(1.f), pos, rotation),
			dimensional<float>(width, height),
			m_zoom(zoom)
		{}
	protected:
		glm::mat4 compute_projection(float width, float height)
		{
			return compute_initial_projection(width, height, m_zoom);
		}
	private:
		glm::mat4 compute_initial_projection(float width, float height, float zoom)
		{
			const float z = 1.f / zoom;
			return glm::ortho(-z, z, -height / width * z, height / width * z);
		}
	};
}
