#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

inline ID3D11Device* g_pd3dDevice = nullptr;
inline ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
inline IDXGISwapChain* g_pSwapChain = nullptr;
inline bool g_SwapChainOccluded = false;
inline UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
inline ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

class DirectX11 {
public:
	bool CreateDeviceD3D(HWND hWnd);
	void CreateRenderTarget();
	void CleanupDeviceD3D();
	void CleanupRenderTarget();
	void NewFrame();
	void EndFrame();
	int Render();
	void Shutdown();
	void CustomStyle();
private:
};

