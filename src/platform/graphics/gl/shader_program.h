#pragma once
#include "pch.h"
#include "shader.h"
#include "coga/graphics/shader_program.h"

namespace coga::gl
{
	class shader_program : public coga::gfx::shader_program
	{
	public:
		shader_program(const std::initializer_list<coga::gfx::shader*>& stages);
		COGA_DCM(shader_program);
		~shader_program();
	public:
		void bind() const override
		{
			glUseProgram(m_id);
		}
		void unbind() const override
		{
			glUseProgram(0);
		}
		void set_uniform_bool(const std::string& name, bool b) const override;
		void set_uniform_bool2(const std::string& name, const glm::bvec2& v) const override;
		void set_uniform_bool3(const std::string& name, const glm::bvec3& v) const override;
		void set_uniform_bool4(const std::string& name, const glm::bvec4& v) const override;
		void set_uniform_bool_array(const std::string& name, const bool* const b, size_t count) const override;
		void set_uniform_int(const std::string& name, int i) const override;
		void set_uniform_int2(const std::string& name, const glm::ivec2& v) const override;
		void set_uniform_int3(const std::string& name, const glm::ivec3& v) const override;
		void set_uniform_int4(const std::string& name, const glm::ivec4& v) const override;
		void set_uniform_int_array(const std::string& name, const int* const i, size_t count) const override;
		void set_uniform_uint(const std::string& name, unsigned int i) const override;
		void set_uniform_uint2(const std::string& name, const glm::uvec2& v) const override;
		void set_uniform_uint3(const std::string& name, const glm::uvec3& v) const override;
		void set_uniform_uint4(const std::string& name, const glm::uvec4& v) const override;
		void set_uniform_uint_array(const std::string& name, const unsigned int* const i, size_t count) const override;
		void set_uniform_float(const std::string& name, float f) const override;
		void set_uniform_float2(const std::string& name, const glm::vec2& v) const override;
		void set_uniform_float3(const std::string& name, const glm::vec3& v) const override;
		void set_uniform_float4(const std::string& name, const glm::vec4& v) const override;
		void set_uniform_float_array(const std::string& name, const float* const f, size_t count) const override;
		void set_uniform_float2_array(const std::string& name, const glm::vec2* const f, size_t count) const override;
		void set_uniform_mat3(const std::string& name, const glm::mat3& m) const override;
		void set_uniform_mat4(const std::string& name, const glm::mat4& m) const override;
	private:
		int get_status(GLenum status) const;
		void print_error(const std::string& s) const;
		template<typename T, typename ... A>
		void set_uniform(T fn, const std::string& name, const A& ... args) const
		{
			bind();
			fn(get_uniform_location(name), args...);
		}
		int get_uniform_location(const std::string& name) const
		{
			return get_location(glGetUniformLocation, name);
		}
		/*int get_uniform_block_location(const std::string& name) const
		{
			return get_location(glGetUniformBlockIndex, name);
		}*/
		template<typename T>
		int get_location(T fn, const std::string& name) const
		{
			const auto& cached = m_cache.find(name);
			if (cached != m_cache.end())
				return cached->second;

			int location = fn(m_id, name.c_str());
			if (location == -1)
			{
				COGA_CORE_ERROR("Uniform {} not found", name);
				return -1;
			}

			m_cache[name] = location;
			return location;
		}
	};
}
