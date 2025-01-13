#pragma once
#include <windows.h>
#include <fstream>
#include <filesystem>
#include "json.hpp"

struct Settings {
	std::string settingsFile = "Config.json";
	std::wstring title = L"DirectX11 Imgui Base";
	int width = 730;
	int height = 335;
	std::string exampleValue = "Hello";
};

//Define values to store on settingsFile here
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Settings, exampleValue)

class Config {
public:
	static inline Settings settings{};
	static void Save() {
		try {
			nlohmann::json j = settings;

			std::ofstream file(settings.settingsFile);
			if (!file.is_open()) {
				throw std::runtime_error("Could not open settings file for writing");
			}

			file << std::setw(4) << j;
		} catch (const std::exception& e) {
			OutputDebugStringA(("Failed to save settings: " + std::string(e.what()) + "\n").c_str());
		}
	}

	static void Load() {
		try {
			if (!std::filesystem::exists(settings.settingsFile)) {
				Save();
				return;
			}

			std::ifstream file(settings.settingsFile);
			if (!file.is_open()) {
				throw std::runtime_error("Could not open settings file for reading");
			}

			nlohmann::json j = nlohmann::json::parse(file);
			settings = j.get<Settings>();
		} catch (const std::exception& e) {
			OutputDebugStringA(("Failed to load settings: " + std::string(e.what()) + "\n").c_str());
		}
	}

	static void openConfigFile() {
		if (!std::filesystem::exists(settings.settingsFile)) {
			Save();
			return;
		}

		ShellExecuteA(NULL, "open", settings.settingsFile.c_str(), NULL, NULL, SW_SHOWDEFAULT);
	}
};