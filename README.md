# 🎨 ImGui Base Template - DirectX11

Welcome to the **ImGui Base Template** repository! 🚀 This project provides a **modular and efficient** foundation for building **external applications** or **overlays** using the powerful [ImGui](https://github.com/ocornut/imgui) library with **DirectX11**. Whether you are developing a game overlay, a custom GUI for your software, or any other graphical application, this template will help you get started quickly and efficiently.

---

## 🌟 Features

### 🗂️ Tabbed Interface
- **Pre-configured Tabs**: Includes **Main Tab** and **Settings Tab** for organizing GUI components.
- **Expandability**: Easily add more tabs for modular functionality.

### 🛠️ JSON Configuration
- **Integrated Support**: Uses [nlohmann/json](https://github.com/nlohmann/json) for configuration handling.
- **Effortless Settings Management**: Store and load settings with ease.

### 📝 Logger
- **spdlog Integration**: Configured logging using [spdlog](https://github.com/gabime/spdlog) for high-performance logging.

### 🎮 Keybind System
- **Custom Keybinds**: Define and manage keybinds using the keybind system located in `src/Keybind.cpp`.
- **Multiple Modes**: Supports different key modes such as HOLD, TOGGLE, and ONCE.

### 🎨 ImGui Integration
- **Customizable GUI**: Leverage the power of ImGui for creating custom user interfaces.
- **DirectX11 Compatibility**: Seamlessly integrates with DirectX11 for rendering.

---

## 📸 Showcase
https://github.com/user-attachments/assets/c73fe215-2c09-456b-8774-ed008eb42d35

---

## ⚙️ Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:
1. **Windows OS**: Ensure you are running a Windows operating system.
2. **Visual Studio**: Install Visual Studio with the "Desktop development with C++" workload.
3. **DirectX11 Runtime Libraries**: Make sure the DirectX11 runtime libraries are installed.

### Steps to Run

Follow these steps to get started with the project:
1. **Clone the repository**:
    ```bash
    git clone https://github.com/voidsocram/imgui-base.git
    ```
2. **Open the solution**: Open the solution file `imgui-base.sln` in Visual Studio.
3. **Build the project**: Set the configuration to **Release** and build the project.
4. **Run the application**: Execute the built application.
