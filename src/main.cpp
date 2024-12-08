#include "DirectX11.h"
#include "Config.h"
#include "resource.h"

DirectX11 DX11;
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPWSTR /*lpCmdLine*/, int /*nCmdShow*/) {
    Config::Load();

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1)), nullptr, nullptr, nullptr, Settings::Window::Title.c_str(), nullptr };
    ::RegisterClassExW(&wc);

    // Get the screen width and height
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int xPos = (screenWidth - Settings::Window::Width) / 2;
    int yPos = (screenHeight - Settings::Window::Height) / 2;

    HWND hwnd = ::CreateWindowW(wc.lpszClassName, Settings::Window::Title.c_str(), WS_OVERLAPPEDWINDOW, xPos, yPos, Settings::Window::Width, Settings::Window::Height, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!DX11.CreateDeviceD3D(hwnd)) {
        DX11.CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Main loop
    bool done = false;
    while (!done) {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window being minimized or screen locked
        if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED) {
            ::Sleep(10);
            continue;
        }
        g_SwapChainOccluded = false;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0) {
            DX11.CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            DX11.CreateRenderTarget();

            RECT rect;
            if (GetWindowRect(hwnd, &rect)) {
                Settings::Window::Height = rect.bottom - rect.top;
                Settings::Window::Width = rect.right - rect.left;
            }
        }

        // Start the Dear ImGui frame
        DX11.NewFrame();
        
        //Render menu
        DX11.Render();

        //End rendering
        DX11.EndFrame();
    }

    // Cleanup
    DX11.Shutdown();

    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
