#pragma once
#include "imgui.h"
#include "Keybind.h"
#include "Logger.h"

class MainTab {
public:

	static void Render() {
		if (ImGui::BeginTabItem("Main")) {

			//Keybinds usage examples
			static Keybind toggleKey('T', KeyMode::TOGGLE, nullptr);
			static Keybind holdKey('E', KeyMode::HOLD, nullptr);
			static Keybind onceKey('J', KeyMode::ONCE, []() {
				Logger::INFO("oncekey func executed !");
			});

			if (toggleKey.RenderKeySelector("Toggle Key")) {
				Logger::INFO("Key changed to: {}", toggleKey.KeyName());
			}

			if (holdKey.RenderKeySelector("Hold Key")) {
				Logger::INFO("Key changed to: {}", holdKey.KeyName());
			}

			if (onceKey.RenderKeySelector("Once Key")) {
				Logger::INFO("Key changed to: {}", onceKey.KeyName());
			}

			ImGui::Text("Current state: %s", toggleKey.IsActive() ? "Active" : "Inactive");

			if (holdKey.IsActive()) {
				ImGui::Text("Holding key %s", holdKey.KeyName());
			}

			ImGui::EndTabItem();
		}
	}
};