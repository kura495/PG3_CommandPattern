#include"ImGuiManager.h"

ImGuiManager* ImGuiManager::GetInstance()
{
	static ImGuiManager instance;
	return &instance;
}

void ImGuiManager::Initialize(WinApp*winapp,DirectXCommon*directXcommon)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winapp->GetHWND());
	ImGui_ImplDX12_Init(directXcommon->GetDevice(), directXcommon->GetSwapChainDesc().BufferCount, directXcommon->GetrtvDesc().Format,
		directXcommon->GetsrvDescriptorHeap().Get(),
		directXcommon->GetsrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
		directXcommon->GetsrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());

}

void ImGuiManager::BeginFrame()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::EndFrame()
{
	ImGui::Render();
}
