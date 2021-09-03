#pragma once
#include "pch.h"



// engine
#include "coga/application.h"
#include "coga/timestep.h"
#include "coga/window.h"

#include "coga/event/app_event.h"
#include "coga/event/event.h"
#include "coga/event/event_handler.h"
#include "coga/event/event_propagator.h"
#include "coga/event/key_event.h"
#include "coga/event/mouse_event.h"
#include "coga/event/window_event.h"

#include "coga/graphics/buffer.h"
#include "coga/graphics/camera.h"
#include "coga/graphics/context.h"
#include "coga/graphics/framebuffer.h"
#include "coga/graphics/framebuffer_attachment.h"
#include "coga/graphics/render_object.h"
#include "coga/graphics/renderer.h"
#include "coga/graphics/retained_buffer.h"
#include "coga/graphics/retained_texture.h"
#include "coga/graphics/shader.h"
#include "coga/graphics/shader_preprocessor.h"
#include "coga/graphics/shader_program.h"
#include "coga/graphics/shader_type.h"
#include "coga/graphics/texture.h"
#include "coga/graphics/vertex_array.h"
#include "coga/graphics/vertex_array_description.h"

#include "coga/imgui/dockspace.h"
#include "coga/imgui/layer.h"
#include "coga/imgui/window.h"

#include "coga/io/file.h"
#include "coga/io/input.h"
#include "coga/io/input_key.h"
#include "coga/io/input_mouse.h"
#include "coga/io/serializable.h"

#include "coga/layer/layer.h"
#include "coga/layer/layer_stack.h"

#include "coga/util/bank.h"
#include "coga/util/color.h"
#include "coga/util/dimensional.h"
#include "coga/util/functions.h"
#include "coga/util/indexed_list.h"
#include "coga/util/iterable.h"
#include "coga/util/movable.h"
#include "coga/util/point.h"
#include "coga/util/positional.h"
#include "coga/util/range.h"
#include "coga/util/rect.h"
#include "coga/util/rect_packer.h"
#include "coga/util/stateful.h"
#include "coga/util/typed.h"



// render api
#ifdef COGA_RENDER_API_GL
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
	#include "platform/graphics/gl/buffer.h"
	#include "platform/graphics/gl/camera.h"
	#include "platform/graphics/gl/context.h"
	#include "platform/graphics/gl/framebuffer.h"
	#include "platform/graphics/gl/framebuffer_attachment.h"
	#include "platform/graphics/gl/index_buffer.h"
	#include "platform/graphics/gl/retained_buffer.h"
	#include "platform/graphics/gl/retained_index_buffer.h"
	#include "platform/graphics/gl/retained_texture.h"
	#include "platform/graphics/gl/retained_vertex_buffer.h"
	#include "platform/graphics/gl/shader.h"
	#include "platform/graphics/gl/shader_program.h"
	#include "platform/graphics/gl/shader_type.h"
	#include "platform/graphics/gl/texture.h"
	#include "platform/graphics/gl/vertex_array.h"
	#include "platform/graphics/gl/vertex_buffer.h"
#endif



// os
#ifdef COGA_PLATFORM_WINDOWS
	#include "platform/os/windows/windows_layer.h"
	#ifdef MAGE_BUILD_LIB
		#include "platform/os/windows/windows_input.h"
		#include "platform/os/windows/windows_window.h"
	#endif
#endif