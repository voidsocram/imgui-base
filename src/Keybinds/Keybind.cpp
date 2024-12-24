#include "Keybind.h"

std::vector<Keybind*> Keybind::keybinds;

Keybind::Keybind(ImGuiKey inputKey, KeyMode mode, std::function<void()> action)
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

    bool keyPressed = ImGui::IsKeyDown(key);

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
    return ImGui::GetKeyName(key);
}

void Keybind::SetKey(ImGuiKey newKey) {
    if (newKey != ImGuiKey_None) {
        key = newKey;
        isEnabled = false;
        prevKeyState = true;
    }
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
    ImGui::Text("%s", label);
    ImGui::SameLine();

    std::string buttonLabel = isSelectingKey ? "Press any key..." : KeyName();
    std::string buttonId = "##" + std::string(label);

    if (ImGui::Button((buttonLabel + buttonId).c_str())) {
        isSelectingKey = true;
        isEnabled = false;
        prevKeyState = true;
    }

    if (isSelectingKey) {
        for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = static_cast<ImGuiKey>(static_cast<int>(key) + 1)) {
            if (ImGui::IsKeyPressed(key)) {
                SetKey(key);
                isSelectingKey = false;
                changed = true;
                isEnabled = false;
                prevKeyState = true;
                break;
            }
        }

        if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
            isSelectingKey = false;
            isEnabled = false;
            prevKeyState = true;
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