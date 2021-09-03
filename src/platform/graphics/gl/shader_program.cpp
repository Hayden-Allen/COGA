#include "pch.h"
#include "shader_program.h"

namespace coga::gl
{
	shader_program::shader_program(const std::initializer_list<coga::gfx::shader*>& stages) :
		coga::gfx::shader_program(stages)
	{
		m_id = glCreateProgram();

		bool vertex = false, fragment = false;
		for (const coga::gfx::shader* const s : stages)
		{
			vertex |= s->get_priority() == vertex_shader::get_static_priority();
			fragment |= s->get_priority() == fragment_shader::get_static_priority();
			glAttachShader(m_id, s->get_id());
		}

		COGA_CORE_ASSERT(vertex && fragment, "OpenGL shader program must have at least a vertex and fragment shader");

		glLinkProgram(m_id);
		if (get_status(GL_LINK_STATUS) == GL_FALSE)
			print_error("linking");
		glValidateProgram(m_id);
		if (!get_status(GL_VALIDATE_STATUS))
			print_error("validation");
	}
	shader_program::~shader_program()
	{
		glDeleteProgram(m_id);
	}



	void shader_program::set_uniform_bool(const std::string& name, bool b) const
	{
		set_uniform(glUniform1i, name, b);
	}
	void shader_program::set_uniform_bool2(const std::string& name, const glm::bvec2& v) const
	{
		set_uniform(glUniform2i, name, v.x, v.y);
	}
	void shader_program::set_uniform_bool3(const std::string& name, const glm::bvec3& v) const
	{
		set_uniform(glUniform3i, name, v.x, v.y, v.z);
	}
	void shader_program::set_uniform_bool4(const std::string& name, const glm::bvec4& v) const
	{
		set_uniform(glUniform4i, name, v.x, v.y, v.z, v.w);
	}
	void shader_program::set_uniform_bool_array(const std::string& name, const bool* const b, size_t count) const
	{
		set_uniform(glUniform1iv, name, COGA_CAST(GLsizei, count), (const GLint*)b);
	}
	void shader_program::set_uniform_int(const std::string& name, int i) const
	{
		set_uniform(glUniform1i, name, i);
	}
	void shader_program::set_uniform_int2(const std::string& name, const glm::ivec2& v) const
	{
		set_uniform(glUniform2i, name, v.x, v.y);
	}
	void shader_program::set_uniform_int3(const std::string& name, const glm::ivec3& v) const
	{
		set_uniform(glUniform3i, name, v.x, v.y, v.z);
	}
	void shader_program::set_uniform_int4(const std::string& name, const glm::ivec4& v) const
	{
		set_uniform(glUniform4i, name, v.x, v.y, v.z, v.w);
	}
	void shader_program::set_uniform_int_array(const std::string& name, const int* const i, size_t count) const
	{
		set_uniform(glUniform1iv, name, COGA_CAST(GLsizei, count), i);
	}
	void shader_program::set_uniform_uint(const std::string& name, unsigned int i) const
	{
		set_uniform(glUniform1ui, name, i);
	}
	void shader_program::set_uniform_uint2(const std::string& name, const glm::uvec2& v) const
	{
		set_uniform(glUniform2ui, name, v.x, v.y);
	}
	void shader_program::set_uniform_uint3(const std::string& name, const glm::uvec3& v) const
	{
		set_uniform(glUniform3ui, name, v.x, v.y, v.z);
	}
	void shader_program::set_uniform_uint4(const std::string& name, const glm::uvec4& v) const
	{
		set_uniform(glUniform4ui, name, v.x, v.y, v.z, v.w);
	}
	void shader_program::set_uniform_uint_array(const std::string& name, const unsigned int* const i, size_t count) const
	{
		set_uniform(glUniform1uiv, name, COGA_CAST(GLsizei, count), i);
	}
	void shader_program::set_uniform_float(const std::string& name, float f) const
	{
		set_uniform(glUniform1f, name, f);
	}
	void shader_program::set_uniform_float2(const std::string& name, const glm::vec2& v) const
	{
		set_uniform(glUniform2f, name, v.x, v.y);
	}
	void shader_program::set_uniform_float3(const std::string& name, const glm::vec3& v) const
	{
		set_uniform(glUniform3f, name, v.x, v.y, v.z);
	}
	void shader_program::set_uniform_float4(const std::string& name, const glm::vec4& v) const
	{
		set_uniform(glUniform4f, name, v.x, v.y, v.z, v.w);
	}
	void shader_program::set_uniform_float_array(const std::string& name, const float* const f, size_t count) const
	{
		set_uniform(glUniform1fv, name, COGA_CAST(GLsizei, count), f);
	}
	void shader_program::set_uniform_float2_array(const std::string& name, const glm::vec2* const f, size_t count) const
	{
		set_uniform(glUniform2fv, name, COGA_CAST(GLsizei, count), (const GLfloat*)f);
	}
	void shader_program::set_uniform_mat3(const std::string& name, const glm::mat3& m) const
	{
		set_uniform(glUniformMatrix3fv, name, 1, GL_FALSE, &m[0][0]);
	}
	void shader_program::set_uniform_mat4(const std::string& name, const glm::mat4& m) const
	{
		set_uniform(glUniformMatrix4fv, name, 1, GL_FALSE, &m[0][0]);
	}



	int shader_program::get_status(GLenum status) const
	{
		int result;
		glGetProgramiv(m_id, status, &result);
		return result;
	}
	void shader_program::print_error(const std::string& s) const
	{
		COGA_CORE_ERROR("OpenGL shader program {} error", s);

		int length = get_status(GL_INFO_LOG_LENGTH);
		char* buf = new char[length];
		glGetProgramInfoLog(m_id, length, nullptr, buf);
		COGA_CORE_ERROR("{}", buf);
		delete[] buf;

		glDeleteProgram(m_id);
		COGA_CORE_ASSERT(false, "");
	}
}
