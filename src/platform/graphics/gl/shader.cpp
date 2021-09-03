#include "pch.h"
#include "shader.h"

namespace coga::gfx
{
	coga::gfx::vertex_shader* coga::gfx::vertex_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new coga::gl::vertex_shader(s, p);
	}
	coga::gfx::fragment_shader* coga::gfx::fragment_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new coga::gl::fragment_shader(s, p);
	}
	coga::gfx::tessellation_control_shader* coga::gfx::tessellation_control_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new coga::gl::tessellation_control_shader(s, p);
	}
	coga::gfx::tessellation_eval_shader* coga::gfx::tessellation_eval_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new coga::gl::tessellation_eval_shader(s, p);
	}
	coga::gfx::geometry_shader* coga::gfx::geometry_shader::create(const std::string& s, const shader_preprocessor& p)
	{
		return new coga::gl::geometry_shader(s, p);
	}
}



namespace coga::gl
{
	template<GLenum TARGET>
	shader<TARGET>::~shader()
	{
		glDeleteShader(m_id);
	}



	template<GLenum TARGET>
	shader<TARGET>::shader(const std::string& s, const coga::gfx::shader_preprocessor& p) :
		coga::gfx::shader(s, p)
	{
		compile(parse(s, p));
	}



	template<GLenum TARGET>
	int shader<TARGET>::get_status(GLenum status) const
	{
		int result;
		glGetShaderiv(m_id, status, &result);
		return result;
	}
	template<GLenum TARGET>
	std::string shader<TARGET>::parse(const std::string& s, const coga::gfx::shader_preprocessor& p) const
	{
		std::ifstream in(s);
		COGA_CORE_ASSERT(in.is_open(), "Error opening OpenGL shader file {}", s);

		std::string line;
		std::stringstream src;

		while (getline(in, line))
			src << p(line) << '\n';

		return src.str();
	}
	template<GLenum TARGET>
	void shader<TARGET>::compile(const std::string& src)
	{
		m_id = glCreateShader(TARGET);
		const char* ptr = src.c_str();
		glShaderSource(m_id, 1, &ptr, nullptr);

		glCompileShader(m_id);
		if (!get_status(GL_COMPILE_STATUS))
		{
			COGA_CORE_ERROR("OpenGL shader compilation failed");
			COGA_CORE_ERROR("Source:\n{}", src.c_str());

			int length = get_status(GL_INFO_LOG_LENGTH);
			char* buf = new char[length];
			glGetShaderInfoLog(m_id, length, nullptr, buf);
			// remove automatic newline
			buf[length - 2] = 0;
			COGA_CORE_ERROR("{}", buf);
			delete[] buf;

			glDeleteShader(m_id);
			COGA_CORE_ASSERT(false, "");
		}
	}
}
