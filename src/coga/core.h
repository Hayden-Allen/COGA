#pragma once
// for convenience to delete copy/move constructors
#define COGA_DCM(name) \
	name(const name& other) = delete; \
	name(name&& other) = delete;
#define COGA_DC(name) \
	name(const name& other) = delete;
#define COGA_DM(name) \
	name(name&& other) = delete;
// additional utils
#define COGA_BIT(x) (1 << x)
#define COGA_CAST(T, x) static_cast<T>(x)
#define COGA_PUN(T, x) *(T*)&x
#define COGA_MTU ::coga::gfx::context::get_max_texture_units()
#define COGA_APP ::coga::application::get()
#define COGA_WIN ::coga::application::get().get_window()
#define COGA_IN ::coga::input::get()
