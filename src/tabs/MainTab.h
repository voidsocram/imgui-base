#pragma once
#include "imgui.h"
#include "Keybinds/Keybind.h"

class MainTab {
public:

	static void Render() {
		if (ImGui::BeginTabItem("Main")) {

			//Keybinds usage examples
			static Keybind toggleKey('T', KeyMode::TOGGLE, nullptr);
			static Keybind holdKey('E', KeyMode::HOLD, nullptr);
			static Keybind onceKey('J', KeyMode::ONCE, []() {
				ShellExecuteA(NULL, "open", Settings::SettingsFile, NULL, NULL, SW_SHOWDEFAULT);
			});

			if (toggleKey.RenderKeySelector("Toggle Key")) {
				std::cout << "Key changed to: " << toggleKey.KeyName() << std::endl;
			}

			if (holdKey.RenderKeySelector("Hold Key")) {
				std::cout << "Key changed to: " << holdKey.KeyName() << std::endl;
			}

			if (onceKey.RenderKeySelector("Once Key")) {
				std::cout << "Key changed to: " << onceKey.KeyName() << std::endl;
			}

			ImGui::Text("Current state: %s", toggleKey.IsActive() ? "Active" : "Inactive");

			if (holdKey.IsActive()) {
				ImGui::Text("Holding key %s", holdKey.KeyName());
			}

			ImGui::EndTabItem();
		}
	}
};