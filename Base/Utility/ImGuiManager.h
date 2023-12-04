#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
class ImGuiManager
{
public:
	static ImGuiManager* GetInstance();
	void Initialize(WinApp* winapp,DirectXCommon*directXcommon);
	void BeginFrame();
	void EndFrame();
private:
	ImGuiManager() = default;
	~ImGuiManager() = default;
	ImGuiManager(const ImGuiManager& obj) = delete;
	ImGuiManager& operator=(const ImGuiManager& obj) = delete;
};