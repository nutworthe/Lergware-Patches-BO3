#include "styles.h"

ImColor menu_rgb()
{

    {
        if (flHue > 255.0f)
            flHue = 0.0f;
    }

    flHue += (rgb_speed / ImGui::GetIO().Framerate);

    ImColor EspPnDColorsrgb_menu = ImColor::HSV(flHue, 1.f, 1.f, 0.7f);
    return EspPnDColorsrgb_menu;
}

void rgbstyle()
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    vec2_t res = { desktop.right, desktop.bottom };

    ImColor menu_rgb_c = menu_rgb();

    auto& style = ImGui::GetStyle();

    ImGui::SetNextWindowSize(ImVec2(518, 490), ImGuiCond_Once);

    style.Colors[ImGuiCol_Separator] = ImColor(20, 20, 20, 200);
    style.Colors[ImGuiCol_SeparatorActive] = ImColor(20, 20, 20, 200);
    style.Colors[ImGuiCol_SeparatorHovered] = ImColor(20, 20, 20, 200);
    style.Colors[ImGuiCol_PlotLines] = ImColor(210, 210, 210, 255);
    style.Colors[ImGuiCol_PlotLinesHovered] = menu_rgb_c;
    style.Colors[ImGuiCol_PlotHistogram] = ImColor(210, 210, 210, 255);
    style.Colors[ImGuiCol_PlotHistogramHovered] = menu_rgb_c;
    style.Colors[ImGuiCol_Text] = ImColor(245, 245, 245, 255);
    style.Colors[ImGuiCol_Border] = ImColor(18, 18, 18, 255);
    style.Colors[ImGuiCol_WindowBg] = ImColor(30, 30, 30, 255);
    style.Colors[ImGuiCol_TitleBg] = menu_rgb_c;
    style.Colors[ImGuiCol_TitleBgActive] = menu_rgb_c;
    style.Colors[ImGuiCol_TitleBgCollapsed] = menu_rgb_c;
    style.Colors[ImGuiCol_Button] = ImColor(20, 20, 20, 200);			// button color
    style.Colors[ImGuiCol_ButtonActive] = menu_rgb_c;	// button color when pressed
    style.Colors[ImGuiCol_ButtonHovered] = ImColor(100, 100, 100, 100);
    style.Colors[ImGuiCol_CheckMark] = menu_rgb_c;
    style.Colors[ImGuiCol_FrameBg] = ImColor(18, 18, 18, 255);
    style.Colors[ImGuiCol_FrameBgActive] = ImColor(18, 18, 18, 255);
    style.Colors[ImGuiCol_FrameBgHovered] = ImColor(18, 18, 18, 255);
    style.Colors[ImGuiCol_Header] = menu_rgb_c;			// for collapsing headers , etc
    style.Colors[ImGuiCol_HeaderActive] = ImColor(24, 24, 24, 255);
    style.Colors[ImGuiCol_HeaderHovered] = menu_rgb_c;
    style.Colors[ImGuiCol_ResizeGrip] = ImColor(24, 24, 24, 255);		// the resize grip thing bottom right
    style.Colors[ImGuiCol_ResizeGripActive] = menu_rgb_c;	// when you hold it / active
    style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(24, 24, 24, 255);
    style.Colors[ImGuiCol_SliderGrab] = menu_rgb_c;
    style.Colors[ImGuiCol_SliderGrabActive] = menu_rgb_c;
    style.Colors[ImGuiCol_Tab] = menu_rgb_c;
    style.Colors[ImGuiCol_MenuBarBg] = menu_rgb_c;
    style.Colors[ImGuiCol_TabHovered] = ImColor(5, 5, 5, 255);
    style.Colors[ImGuiCol_TabActive] = ImColor(5, 5, 5, 255);
    style.Colors[ImGuiCol_TabUnfocused] = menu_rgb_c;
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImColor(5, 5, 5, 255);
    style.Colors[ImGuiCol_TextSelectedBg] = menu_rgb_c;

    style.WindowPadding = ImVec2(6, 4);
    style.WindowRounding = 10.f;
    style.FramePadding = ImVec2(5, 2);
    style.FrameRounding = 4.0f;
    style.ItemSpacing = ImVec2(7, 1);
    style.ItemInnerSpacing = ImVec2(1, 1);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing = 6.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;
    style.GrabMinSize = 20.0f;
    style.GrabRounding = 2.0f;
    style.WindowTitleAlign.x = 0.50f;
    style.FrameBorderSize = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.ItemInnerSpacing = ImVec2(5, 0);
}