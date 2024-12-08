#pragma once
#include "json.hpp"
#include <windows.h>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

namespace Settings {
	// Global HWND (window handle)
	inline HWND hwnd;

	inline constexpr const char* SettingsFile = "Config.json";
	inline std::string defaultValue;

	namespace Window {
		inline const std::wstring Title = L"DirectX11 Imgui Base";
		inline int Width = 730;
		inline int Height = 335;
	}
}

class Config {
public:

	static void Save() {
		std::ifstream iFile(Settings::SettingsFile);
		if (iFile.good()) {
			json data = json::parse(iFile);
			data["defaultValue"] = Settings::defaultValue;

			std::ofstream oFile(Settings::SettingsFile);
			oFile << data.dump(4) << std::endl;
			oFile.close();
		}
		iFile.close();
	}

	static void Load() {
		// if file doesn't exist, create new one
		if (!std::filesystem::exists(Settings::SettingsFile)) {

			nlohmann::json defaultSettings = {
				{"defaultValue", ""},
			};

			std::ofstream file(Settings::SettingsFile);
			file << defaultSettings.dump(4);
			file.close();
		}

		std::fstream file(Settings::SettingsFile, std::ios_base::in);
		if (file.good()) {
			json data = json::parse(file);

			if (data.contains("defaultValue")) Settings::defaultValue = data["defaultValue"];
		}
		file.close();
	}
};