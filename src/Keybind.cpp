#include "Keybind.h"
#include <Windows.h>

std::vector<Keybind*> Keybind::keybinds;
const std::unordered_map<int, std::string> Keybind::VK_TO_STRING = {
	{VK_LBUTTON, "Left Mouse"},
	{VK_RBUTTON, "Right Mouse"},
	{VK_MBUTTON, "Middle Mouse"},
	{VK_BACK, "Backspace"},
	{VK_TAB, "Tab"},
	{VK_RETURN, "Enter"},
	{VK_SHIFT, "Shift"},
	{VK_CONTROL, "Control"},
	{VK_MENU, "Alt"},
	{VK_PAUSE, "Pause"},
	{VK_CAPITAL, "Caps Lock"},
	{VK_ESCAPE, "Escape"},
	{VK_SPACE, "Space"},
	{VK_PRIOR, "Page Up"},
	{VK_NEXT, "Page Down"},
	{VK_END, "End"},
	{VK_HOME, "Home"},
	{VK_LEFT, "Left"},
	{VK_UP, "Up"},
	{VK_RIGHT, "Right"},
	{VK_DOWN, "Down"},
	{VK_INSERT, "Insert"},
	{VK_DELETE, "Delete"},
	{'0', "0"}, {'1', "1"}, {'2', "2"}, {'3', "3"}, {'4', "4"},
	{'5', "5"}, {'6', "6"}, {'7', "7"}, {'8', "8"}, {'9', "9"},
	{'A', "A"}, {'B', "B"}, {'C', "C"}, {'D', "D"}, {'E', "E"},
	{'F', "F"}, {'G', "G"}, {'H', "H"}, {'I', "I"}, {'J', "J"},
	{'K', "K"}, {'L', "L"}, {'M', "M"}, {'N', "N"}, {'O', "O"},
	{'P', "P"}, {'Q', "Q"}, {'R', "R"}, {'S', "S"}, {'T', "T"},
	{'U', "U"}, {'V', "V"}, {'W', "W"}, {'X', "X"}, {'Y', "Y"},
	{'Z', "Z"},
	{VK_NUMPAD0, "Numpad 0"}, {VK_NUMPAD1, "Numpad 1"},
	{VK_NUMPAD2, "Numpad 2"}, {VK_NUMPAD3, "Numpad 3"},
	{VK_NUMPAD4, "Numpad 4"}, {VK_NUMPAD5, "Numpad 5"},
	{VK_NUMPAD6, "Numpad 6"}, {VK_NUMPAD7, "Numpad 7"},
	{VK_NUMPAD8, "Numpad 8"}, {VK_NUMPAD9, "Numpad 9"},
	{VK_F1, "F1"}, {VK_F2, "F2"}, {VK_F3, "F3"}, {VK_F4, "F4"},
	{VK_F5, "F5"}, {VK_F6, "F6"}, {VK_F7, "F7"}, {VK_F8, "F8"},
	{VK_F9, "F9"}, {VK_F10, "F10"}, {VK_F11, "F11"}, {VK_F12, "F12"}
};

Keybind::Keybind(int inputKey, KeyMode mode, std::function<void()> action)
	: key(inputKey)
	, mode(mode)
	, isEnabled(false)
	, prevKeyState(false)
	, isSelectingKey(false)
	, action(action) {
	keybinds.push_back(this);
}

Keybind::~Keybind() {
	auto it = std::find(keybinds.begin(), keybinds.end(), this);
	if (it != keybinds.end()) {
		keybinds.erase(it);
	}
}

void Keybind::Update() {
	if (isSelectingKey) return;

	bool keyPressed = (GetAsyncKeyState(key) & 0x8000) != 0;

	switch (mode) {
	case KeyMode::HOLD:
		isEnabled = keyPressed;
		break;

	case KeyMode::TOGGLE:
		if (keyPressed && !prevKeyState) {
			isEnabled = !isEnabled;
		}
		break;

	case KeyMode::ONCE:
		isEnabled = keyPressed && !prevKeyState;
		break;
	}

	if (isEnabled && action) {
		action();
	}

	prevKeyState = keyPressed;
}

bool Keybind::IsActive() const {
	return isEnabled;
}

std::string Keybind::KeyName() const {
	auto it = VK_TO_STRING.find(key);
	if (it != VK_TO_STRING.end()) {
		return it->second;
	}
	return "Unknown";
}

void Keybind::SetKey(int newKey) {
	key = newKey;
	isEnabled = false;
	prevKeyState = true;
}

void Keybind::SetMode(KeyMode newMode) {
	mode = newMode;
	isEnabled = false;
}

void Keybind::SetAction(std::function<void()> newAction) {
	action = newAction;
}

bool Keybind::RenderKeySelector(const char* label) {
	bool changed = false;
	ImGui::Text(label);
	ImGui::SameLine();

	std::string buttonLabel = isSelectingKey ? "Press any key..." : KeyName();
	std::string buttonId = "##" + std::string(label);

	if (ImGui::Button((buttonLabel + buttonId).c_str())) {
		isSelectingKey = true;
		isEnabled = false;
		prevKeyState = true;
	}

	if (isSelectingKey) {
		for (const auto& [vk, name] : VK_TO_STRING) {

			//Cancel key selection if ESC is pressed
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				isSelectingKey = false;
				isEnabled = false;
				prevKeyState = true;
				break;
			}

			if (GetAsyncKeyState(vk) & 0x8000) {
				SetKey(vk);
				isSelectingKey = false;
				changed = true;
				isEnabled = false;
				prevKeyState = true;
				break;
			}
		}

	}

	return changed;
}

void Keybind::UpdateAll() {
	for (auto& keybind : keybinds) {
		keybind->Update();
	}
}

void Keybind::ClearAll() {
	keybinds.clear();
}