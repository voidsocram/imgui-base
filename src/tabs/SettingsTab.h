#pragma once
#include "imgui.h"

class SettingsTab {
public:

    static void Render() {
        if (ImGui::BeginTabItem("Settings")) {

            if (ImGui::Button("Open Config File")) {
                ShellExecuteA(NULL, "open", Settings::SettingsFile, NULL, NULL, SW_SHOWDEFAULT);
            }

            ImGui::EndTabItem();
        }
    }
};