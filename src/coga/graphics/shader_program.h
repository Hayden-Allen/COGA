#pragma once
#include "../vendor/glm/glm/glm.hpp"
#include "../log.h"
#include "render_object.h"
#include "shader.h"

namespace coga::gfx
{
	class shader_program : public render_object
	{
	public:
		COGA_DCM(shader_program);
		virtual ~shader_program()
		{
			for (const shader* const s : m_stages)
				delete s;
		}
	public:
		virtual void set_uniform_bool(const std::string& name, bool b) const = 0;
		virtual void set_uniform_bool2(const std::string& name, const glm::bvec2& v) const = 0;
		virtual void set_uniform_bool3(const std::string& name, const glm::bvec3& v) const = 0;
		virtual void set_uniform_bool4(const std::string& name, const glm::bvec4& v) const = 0;
		virtual void set_uniform_bool_array(const std::string& name, const bool* const b, size_t count) const = 0;
		virtual void set_uniform_int(const std::string& name, int i) const = 0;
		virtual void set_uniform_int2(const std::string& name, const glm::ivec2& v) const = 0;
		virtual void set_uniform_int3(const std::string& name, const glm::ivec3& v) const = 0;
		virtual void set_uniform_int4(const std::string& name, const glm::ivec4& v) const = 0;
		virtual void set_uniform_int_array(const std::string& name, const int* const i, size_t count) const = 0;
		virtual void set_uniform_uint(const std::string& name, unsigned int i) const = 0;
		virtual void set_uniform_uint2(const std::string& name, const glm::uvec2& v) const = 0;
		virtual void set_uniform_uint3(const std::string& name, const glm::uvec3& v) const = 0;
		virtual void set_uniform_uint4(const std::string& name, const glm::uvec4& v) const = 0;
		virtual void set_uniform_uint_array(const std::string& name, const unsigned int* const i, size_t count) const = 0;
		virtual void set_uniform_float(const std::string& name, float f) const = 0;
		virtual void set_uniform_float2(const std::string& name, const glm::vec2& v) const = 0;
		virtual void set_uniform_float3(const std::string& name, const glm::vec3& v) const = 0;
		virtual void set_uniform_float4(const std::string& name, const glm::vec4& v) const = 0;
		virtual void set_uniform_float_array(const std::string& name, const float* const f, size_t count) const = 0;
		virtual void set_uniform_float2_array(const std::string& name, const glm::vec2* const f, size_t count) const = 0;
		virtual void set_uniform_mat3(const std::string& name, const glm::mat3& m) const = 0;
		virtual void set_uniform_mat4(const std::string& name, const glm::mat4& m) const = 0;
	protected:
		std::vector<shader*> m_stages;
		mutable std::unordered_map<std::string, int> m_cache;
	protected:
		shader_program(const std::initializer_list<shader*>& stages) :
			m_stages(stages)
		{
			int last = -1;
			for (const shader* const s : stages)
			{
				shader_priority_t cur = s->get_priority();
				COGA_ASSERT(COGA_CAST(int, cur) > last, "Invalid shader priorty {} (must be >{})", cur, last);
				last = cur;
			}
		}
	};
}
