//
// Created by Antilles on 1/29/2023.
//

#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

struct LocalImguiSettings
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
};


void vw_fc_home(bool* p_open)
{
    //Global theme
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 255);

    auto local_settings = LocalImguiSettings{};
    ImGui::SetNextWindowPos(local_settings.viewport->WorkPos);
    ImGui::SetNextWindowSize(local_settings.viewport->WorkSize);
    if (ImGui::Begin("FlashCard Game: Home Window", p_open, local_settings.flags))
    {
        ImGui::Text("Pick a card game:");

        if (p_open && ImGui::Button("Close this window"))
            *p_open = false;
    }
    ImGui::End();
}

void vw_fc_question(bool* p_open)
{
    auto local_settings = LocalImguiSettings{};
    ImGui::SetNextWindowPos(local_settings.viewport->WorkPos);
    ImGui::SetNextWindowSize(local_settings.viewport->WorkSize);
    if (ImGui::Begin("Question View", p_open, local_settings.flags))
    {
        ImGui::Text("Question:");

        if (p_open && ImGui::Button("Close this window"))
            *p_open = false;
    }
    ImGui::End();
}