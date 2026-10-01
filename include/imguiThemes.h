#pragma once

#include "imgui.h"

// Ready made Dear ImGui palettes. Call one right after ImGui::CreateContext():
//
//     ImGui::CreateContext();
//     imguiThemes::yellow();
//
// Every theme starts from ImGui's own dark palette and then tints the interactive
// slots (buttons, sliders, checkmarks, tabs, separators) with that theme's highlight,
// so the five of them stay consistent with each other.

namespace imguiThemes
{

inline ImVec4 lerp(const ImVec4& a, const ImVec4& b, float t)
{
	return ImVec4(a.x + (b.x - a.x) * t,
				  a.y + (b.y - a.y) * t,
				  a.z + (b.z - a.z) * t,
				  a.w + (b.w - a.w) * t);
}

inline void applyTheme(const ImVec4& accent, const ImVec4& bg)
{
	ImGui::StyleColorsDark();

	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_WindowBg]               = ImVec4(bg.x, bg.y, bg.z, 0.94f);
	colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg]                = ImVec4(bg.x, bg.y, bg.z, 0.94f);
	colors[ImGuiCol_Border]                 = ImVec4(accent.x, accent.y, accent.z, 0.50f);
	colors[ImGuiCol_TitleBgActive]          = lerp(colors[ImGuiCol_TitleBg], accent, 0.35f);
	colors[ImGuiCol_MenuBarBg]              = lerp(colors[ImGuiCol_TitleBg], accent, 0.10f);

	colors[ImGuiCol_FrameBgHovered]         = ImVec4(accent.x, accent.y, accent.z, 0.40f);
	colors[ImGuiCol_FrameBgActive]          = ImVec4(accent.x, accent.y, accent.z, 0.67f);
	colors[ImGuiCol_CheckboxSelectedBg]     = lerp(colors[ImGuiCol_FrameBg], colors[ImGuiCol_FrameBgHovered], 0.65f);

	colors[ImGuiCol_CheckMark]              = accent;
	colors[ImGuiCol_SliderGrab]             = lerp(accent, ImVec4(0.00f, 0.00f, 0.00f, 1.00f), 0.15f);
	colors[ImGuiCol_SliderGrabActive]       = accent;

	colors[ImGuiCol_Button]                 = ImVec4(accent.x, accent.y, accent.z, 0.40f);
	colors[ImGuiCol_ButtonHovered]          = accent;
	colors[ImGuiCol_ButtonActive]           = lerp(accent, ImVec4(0.00f, 0.00f, 0.00f, 1.00f), 0.20f);

	colors[ImGuiCol_Header]                 = ImVec4(accent.x, accent.y, accent.z, 0.31f);
	colors[ImGuiCol_HeaderHovered]          = ImVec4(accent.x, accent.y, accent.z, 0.80f);
	colors[ImGuiCol_HeaderActive]           = accent;

	colors[ImGuiCol_Separator]              = colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered]       = accent;
	colors[ImGuiCol_SeparatorActive]        = accent;

	colors[ImGuiCol_ResizeGrip]             = ImVec4(accent.x, accent.y, accent.z, 0.20f);
	colors[ImGuiCol_ResizeGripHovered]      = ImVec4(accent.x, accent.y, accent.z, 0.67f);
	colors[ImGuiCol_ResizeGripActive]       = ImVec4(accent.x, accent.y, accent.z, 0.95f);

	colors[ImGuiCol_InputTextCursor]        = accent;

	colors[ImGuiCol_TabHovered]             = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_Tab]                    = lerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
	colors[ImGuiCol_TabSelected]            = lerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
	colors[ImGuiCol_TabSelectedOverline]    = colors[ImGuiCol_HeaderActive];
	colors[ImGuiCol_TabDimmed]              = lerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabDimmedSelected]      = lerp(colors[ImGuiCol_TabSelected], colors[ImGuiCol_TitleBg], 0.40f);

	colors[ImGuiCol_DockingPreview]         = ImVec4(colors[ImGuiCol_HeaderActive].x, colors[ImGuiCol_HeaderActive].y, colors[ImGuiCol_HeaderActive].z, 0.70f);
	colors[ImGuiCol_DockingEmptyBg]         = lerp(colors[ImGuiCol_WindowBg], ImVec4(0.00f, 0.00f, 0.00f, 1.00f), 0.30f);

	colors[ImGuiCol_TextLink]               = colors[ImGuiCol_HeaderActive];
	colors[ImGuiCol_TextSelectedBg]         = ImVec4(accent.x, accent.y, accent.z, 0.35f);
	colors[ImGuiCol_TreeLines]              = colors[ImGuiCol_Border];

	colors[ImGuiCol_DragDropTarget]         = accent;
	colors[ImGuiCol_UnsavedMarker]          = colors[ImGuiCol_Text];

	colors[ImGuiCol_NavCursor]              = accent;
	colors[ImGuiCol_NavWindowingHighlight]  = colors[ImGuiCol_HeaderActive];
	colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(accent.x, accent.y, accent.z, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(accent.x, accent.y, accent.z, 0.35f);
}

// warm amber highlight on a near-black background
inline void yellow() { applyTheme(ImVec4(1.00f, 0.83f, 0.30f, 1.00f), ImVec4(0.07f, 0.07f, 0.06f, 1.00f)); }

// neutral highlight with no color cast
inline void gray()   { applyTheme(ImVec4(0.72f, 0.74f, 0.78f, 1.00f), ImVec4(0.07f, 0.07f, 0.07f, 1.00f)); }

inline void green()  { applyTheme(ImVec4(0.44f, 0.86f, 0.51f, 1.00f), ImVec4(0.05f, 0.07f, 0.06f, 1.00f)); }

inline void red()    { applyTheme(ImVec4(0.95f, 0.36f, 0.36f, 1.00f), ImVec4(0.08f, 0.05f, 0.05f, 1.00f)); }

// deep blue-black, deliberately low contrast, to sit behind a fullscreen render
inline void embraceTheDarkness() { applyTheme(ImVec4(0.30f, 0.36f, 0.45f, 1.00f), ImVec4(0.03f, 0.03f, 0.04f, 1.00f)); }

}
