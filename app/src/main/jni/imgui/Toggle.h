#pragma once
#include "imgui_internal.h"

inline void ToggleSwitch(const char* label, bool* v)
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = 24.0f;
    float width = height * 1.8f;
    float radius = height * 0.5f;

    ImGui::InvisibleButton(label, ImVec2(width, height));
    if (ImGui::IsItemClicked())
        *v = !*v;

    float t = *v ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;
    float ANIM_SPEED = 0.12f;
    if (g.LastActiveId == g.CurrentWindow->GetID(label))
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = *v ? t_anim : (1.0f - t_anim);
    }

    ImU32 col_bg = *v
        ? IM_COL32(8, 132, 255, 255)   // Sleek Blue
        : IM_COL32(45, 45, 55, 255);    // Dark Gray Off state

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddRect(p, ImVec2(p.x + width, p.y + height), IM_COL32(80, 140, 220, 100), height * 0.5f, 0, 1.0f);

    float thumb_x = p.x + radius + t * (width - radius * 2.0f);
    draw_list->AddCircleFilled(ImVec2(thumb_x, p.y + radius), radius - 2.5f, IM_COL32(255, 255, 255, 255));
}

inline void ToggleSwitchFloat(const char* label, bool* v)
{
    ToggleSwitch(label, v);
}
