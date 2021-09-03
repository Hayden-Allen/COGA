#pragma once
#include "pch.h"
#include "coga/graphics/camera.h"

namespace coga::gl
{
	class orthographic_camera : public coga::gfx::orthographic_camera
	{
	public:
		orthographic_camera(event_handler_container& c, float width, float height, const glm::vec3& pos, s_type rotation, float zoom) :
			coga::gfx::orthographic_camera(c, width, height, pos, rotation, zoom)
		{
			update();
		}
		COGA_DCM(orthographic_camera);
	public:
		void set_pos(const glm::vec3& pos) override;
	protected:
		void update() override;
	};
}
