#pragma once
#include <imgui.h>
#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <memory>

enum class KeyMode {
    HOLD,
    TOGGLE,
    ONCE
};

class Keybind {
public:
    Keybind(int inputKey, KeyMode mode, std::function<void()> action = nullptr);
    ~Keybind();

    void Update();
    [[nodiscard]] bool IsActive() const;
    [[nodiscard]] std::string KeyName() const; 
    [[nodiscard]] int GetKey() const { return key; } 
    [[nodiscard]] KeyMode GetMode() const { return mode; }

    void SetKey(int newKey);
    void SetMode(KeyMode newMode);
    void SetAction(std::function<void()> newAction);

    bool RenderKeySelector(const char* label);

    static void UpdateAll();
    static void ClearAll();

private:
    int key;
    KeyMode mode;
    bool isEnabled;
    bool prevKeyState;
    bool isSelectingKey; 
    std::function<void()> action;

    static const std::unordered_map<int, std::string> VK_TO_STRING;
    static std::vector<Keybind*> keybinds;
};