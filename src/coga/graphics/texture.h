#pragma once
#include "pch.h"
#include "render_object.h"
#include "texture_options.h"
#include "coga/io/serializable.h"
#include "coga/util/dimensional.h"

namespace coga::gfx
{
	class texture :
		public render_object,
		public dimensional<uint32_t>
	{
	public:
		COGA_DCM(texture);
		virtual ~texture() {}
	public:
		virtual void bind(uint32_t slot) const = 0;
	protected:
		texture(s_type w, s_type h) :
			dimensional<s_type>(w, h)
		{}
	protected:
		void bind() const override
		{
			bind(0);
		}
	};



	class texture2d : public texture
	{
	public:
		COGA_DCM(texture2d);
		virtual ~texture2d() {}
	public:
		virtual void update(s_type x, s_type y, s_type w, s_type h, const void* const data) = 0;
	protected:
		texture2d(s_type w, s_type h) :
			texture(w, h)
		{}
	};



	class texture2d_array : public texture
	{
	public:
		COGA_DCM(texture2d_array);
		virtual ~texture2d_array() {}
	public:
		virtual void update(s_type x, s_type y, s_type z, s_type w, s_type h, s_type d, const void* const data) = 0;
		s_type get_frame_count() const
		{
			return m_frames;
		}
	protected:
		s_type m_frames;
	protected:
		texture2d_array(s_type w, s_type h, s_type f) :
			texture(w, h),
			m_frames(f)
		{}
	};
}
