#pragma once
#include "pch.h"
#include "texture.h"

namespace coga::gfx
{
	enum class framebuffer_attachment_type
	{
		none = 0,
		color, depth
	};

	template<typename T, typename ... ARGS>
	class framebuffer;

	template<typename T, typename ... ARGS>
	class framebuffer_attachment : public T
	{
	protected:
		friend class framebuffer<T, ARGS...>;
		using s_type = T::s_type;
	public:
		COGA_DCM(framebuffer_attachment);
		virtual ~framebuffer_attachment() {}
	public:
		virtual framebuffer_attachment_type get_type() const = 0;
		virtual void reset() const = 0;
	protected:
		framebuffer_attachment(s_type w, s_type h, const ARGS& ... args) :
			T(w, h, args...)
		{}
	};



	template<typename T, typename ... ARGS>
	class framebuffer_color_attachment : public framebuffer_attachment<T, ARGS...> {
	protected:
		using s_type = framebuffer_attachment<T, ARGS...>::s_type;
	public:
		COGA_DCM(framebuffer_color_attachment);
		virtual ~framebuffer_color_attachment() {}
	public:
		framebuffer_attachment_type get_type() const final override
		{
			return framebuffer_attachment_type::color;
		}
	protected:
		framebuffer_color_attachment(s_type w, s_type h, const ARGS& ... args) :
			framebuffer_attachment<T, ARGS...>(w, h, args...)
		{}
	};



	template<typename T, typename ... ARGS>
	class framebuffer_depth_attachment : public framebuffer_attachment<T, ARGS...>{
	protected:
		using s_type = framebuffer_attachment<T, ARGS...>::s_type;
	public:
		COGA_DCM(framebuffer_depth_attachment);
		virtual ~framebuffer_depth_attachment() {}
	public:
		framebuffer_attachment_type get_type() const final override
		{
			return framebuffer_attachment_type::depth;
		}
	protected:
		framebuffer_depth_attachment(s_type w, s_type h, const ARGS& ... args) :
			framebuffer_attachment<T, ARGS...>(w, h, args...)
		{}
	};
}
