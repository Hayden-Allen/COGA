#include "pch.h"
#include "layer.h"
#include "coga/io/input_key.h"
#include "coga/util/functions.h"
#include "coga/application.h"
#include "coga/log.h"

namespace coga::imgui
{
    uint32_t layer::s_instance_count = 0;



    layer::~layer()
    {
        if (s_instance_count == 0)
            end();
    }



    // propagate COGA events to ImGui
    bool layer::on_app_tick(app_tick_event& e)
    {
        if (m_instance_id == 0)
        {
            app_tick(e);

            float current = COGA_CAST(float, glfwGetTime());
            static float last = 0.f;

            ImGuiIO& io = ImGui::GetIO();
            io.DeltaTime = (last == 0.f ? 1.f : current - last);
            last = current;

            ImGui::NewFrame();
        }
        return false;
    }
    bool layer::on_app_render(app_render_event& e)
    {
        if (m_instance_id == 0)
        {
            ImGuiIO& io = ImGui::GetIO();
            const window& window = application::get().get_window();
            io.DisplaySize = ImVec2(window.get_w<float>(), window.get_h<float>());

            ImGui::Render();

            app_render(e);
        }
        return false;
    }
    bool layer::on_key_press(key_press_event& e)
    {
        on_key_base(e, true);
        return false;
    }
    bool layer::on_key_release(key_release_event& e)
    {
        on_key_base(e, false);
        return false;
    }
    bool layer::on_mouse_press(mouse_press_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        int b = e.get_button();
        if(b >= 0 && b < ImGuiMouseButton_COUNT)
            io.MouseDown[e.get_button()] = true;

        return false;
    }
    bool layer::on_mouse_release(mouse_release_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        int b = e.get_button();
        if (b >= 0 && b < ImGuiMouseButton_COUNT)
            io.MouseDown[e.get_button()] = false;

        return false;
    }
    bool layer::on_mouse_move(mouse_move_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MousePos = ImVec2(e.get_x<float>(), e.get_y<float>());

        return false;
    }
    bool layer::on_mouse_scroll(mouse_scroll_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseWheel += e.get_y();
        io.MouseWheelH += e.get_x();

        return false;
    }
    bool layer::on_window_resize(window_resize_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = ImVec2(e.get_w<float>(), e.get_h<float>());
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);

        return false;
    }
    void layer::on_key_base(key_event& e, bool pressed)
    {
        ImGuiIO& io = ImGui::GetIO();

        int c = e.get_code();
        if (c >= 0 && c < arrlen(io.KeysDown))
            io.KeysDown[c] = pressed;


        io.KeyCtrl = io.KeysDown[coga::key::left_control] || io.KeysDown[coga::key::right_control];
        io.KeyShift = io.KeysDown[coga::key::left_shift] || io.KeysDown[coga::key::right_shift];
        io.KeyAlt = io.KeysDown[coga::key::left_alt] || io.KeysDown[coga::key::right_alt];
    #ifdef MAGE_PLATFORM_WINDOWS
        io.KeySuper = false;
    #else
        io.KeySuper = io.KeysDown[coga::key::left_super] || io.KeysDown[coga::key::right_super];
    #endif
    }



#ifndef MAGE_DIST
    layer::layer(const std::string& name) :
        coga::layer(name),
        m_instance_id(s_instance_count)
    {
        if (s_instance_count == 0)
            init();
    }
#else
    layer::layer()
    {
        if (s_instance_count == 0)
            init();
    }
#endif



    void layer::init()
    {
        // ImGui initialization
        // ONLY CALLED WHEN THE FIRST LAYER IS INSTANTIATED
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        
        // custom theme
        {
            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.f);
            colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.21f, 0.22f, 0.54f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
            colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.46f, 0.47f, 0.48f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(0.70f, 0.70f, 0.70f, 0.31f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.50f, 0.52f, 1.00f);
            colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
            colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
            colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.73f, 0.60f, 0.15f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
            colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_Tab] = ImVec4(0.09f, 0.09f, 0.09f, 1.f);
            colors[ImGuiCol_TabActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
            colors[ImGuiCol_TabUnfocused] = colors[ImGuiCol_Tab];
            colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabActive];
        }

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.f;
        }
    }
    void layer::end()
    {
        ImGui::DestroyContext();
    }
}
