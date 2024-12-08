#pragma once
#include "imgui.h"
class MainTab {
public:

    static void Render() {
        if (ImGui::BeginTabItem("Main")) {

            ImGui::Text("Hello World");

            ImGui::EndTabItem();
        }
    }
};