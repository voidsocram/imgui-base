#pragma once
#include "imgui.h"
#include "Config.h"
#include "Logger.h"

class SettingsTab {
public:

    static void Render() {
        if (ImGui::BeginTabItem("Settings")) {

            if (ImGui::Button("Open Config File")) {
                Config::openConfigFile();
            }    
            
            if (ImGui::Button("Toggle Console")) {
                Logger::ToggleConsole();
            }

            ImGui::EndTabItem();
        }
    }
};