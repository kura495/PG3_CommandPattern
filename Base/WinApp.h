#pragma once
#include<Windows.h>
#include<cstdint>
#include"Log.h"
#include"externals/imgui/imgui.h"
#include"externals/imgui/imgui_impl_dx12.h"
#include"externals/imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
class WinApp
{
public:
	static WinApp*GetInstance();
	static LRESULT  WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void Initialize();
	
	HWND GetHWND() const { return hwnd_; };
	HINSTANCE GetHINSTANCE()const { return wc.hInstance; }
	static const int32_t kClientWidth=1280;//横幅
	static const int32_t kClientHeight=720;//縦幅
private:
	WinApp() = default;
	~WinApp() = default;
	WinApp(const WinApp& obj) = delete;
	WinApp& operator=(const WinApp& obj) = delete;

	HWND hwnd_=nullptr;
	WNDCLASS wc{};

};


