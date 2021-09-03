#pragma once
#include "pch.h"
#include "coga/graphics/shader.h"

namespace coga::gl
{
	template<GLenum TARGET>
	class shader : public coga::gfx::shader
	{
	public:
		COGA_DCM(shader);
		~shader();
	public:
		void bind() const override
		{
			COGA_CORE_ASSERT(false, "OpenGL shaders cannot be bound");
		}
		void unbind() const override
		{
			COGA_CORE_ASSERT(false, "OpenGL shaders cannot be unbound");
		}
	protected:
		shader(const std::string& s, const coga::gfx::shader_preprocessor& p = coga::gfx::shader_preprocessor());
	protected:
		int get_status(GLenum status) const;
		std::string parse(const std::string& s, const coga::gfx::shader_preprocessor& p) const;
		void compile(const std::string& src);
	};



#define S(TARGET, CLASS, PRIORITY, NAME) \
	class CLASS final : public shader<TARGET>, public coga::gfx::CLASS { \
		using shader<TARGET>::m_id; \
	public:\
		CLASS(const std::string& src, const coga::gfx::shader_preprocessor& p = coga::gfx::shader_preprocessor()) : shader<TARGET>(src, p), coga::gfx::CLASS(src, p) {} \
		COGA_DCM(CLASS); \
		void bind() const override { shader<TARGET>::bind(); } \
		void unbind() const override { shader<TARGET>::unbind(); } \
		coga::gfx::renderer_id_t get_id() const override { return shader<TARGET>::m_id; } \
		MAGE_SHADER_PRIORITY(PRIORITY); };

	S(GL_VERTEX_SHADER, vertex_shader, 0, vertex);
	S(GL_TESS_CONTROL_SHADER, tessellation_control_shader, 1, tessellation control);
	S(GL_TESS_EVALUATION_SHADER, tessellation_eval_shader, 2, tessellation evaluation);
	S(GL_GEOMETRY_SHADER, geometry_shader, 3, geometry);
	S(GL_FRAGMENT_SHADER, fragment_shader, 4, fragment);

#undef S
}
