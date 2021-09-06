#include "pch.h"
#include "camera.h"

namespace coga::gl
{
	void orthographic_camera::set_pos(const glm::vec3& pos)
	{
		// for some reason z-values outside of [-1, 1] cause problems. We don't need those anyways for a 2D camera, so just remove it
		coga::gfx::orthographic_camera::set_pos({ pos.x, pos.y, 0.f });
	}



	void orthographic_camera::update()
	{
		// rotate about positive z-axis (pointing out of the screen)
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_pos) * glm::rotate(glm::mat4(1.f), m_rotation, glm::vec3(0, 0, 1));

		m_view = glm::inverse(transform);
		m_view_projection = m_projection * m_view;
	}
}
