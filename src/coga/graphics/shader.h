#pragma once
#include "pch.h"
#include "render_object.h"
#include "shader_preprocessor.h"

namespace coga::gfx
{
	typedef uint32_t shader_priority_t;

#define MAGE_SHADER_PRIORITY(x) \
	static coga::gfx::shader_priority_t get_static_priority() { return x; } \
	virtual coga::gfx::shader_priority_t get_priority() const override { return x; }



	class shader : public render_object
	{
	public:
		COGA_DCM(shader);
		virtual ~shader() {}
	public:
		virtual shader_priority_t get_priority() const = 0;
	protected:
		shader(const std::string& s, const shader_preprocessor& p = shader_preprocessor()) {}
	};



#define S(CLASS) \
	class CLASS : public shader { \
	public: \
		COGA_DCM(CLASS); \
		virtual ~CLASS() {} \
		static CLASS* create(const std::string& s, const shader_preprocessor& p = shader_preprocessor()); \
	protected: \
		CLASS(const std::string& s, const shader_preprocessor& p = shader_preprocessor()) : shader(s, p) {} };

	S(vertex_shader);
	S(tessellation_control_shader);
	S(tessellation_eval_shader);
	S(geometry_shader);
	S(fragment_shader);

#undef S
}
