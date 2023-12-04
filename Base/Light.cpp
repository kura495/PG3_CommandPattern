#include "Light.h"

Light* Light::GetInstance()
{
	static Light instance;
	return &instance;
}

void Light::Initialize()
{
	directX_ = DirectXCommon::GetInstance();

	directionalLightResource = directX_->CreateBufferResource(sizeof(DirectionalLight));
	directionalLightResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));
	directionalLightData->color = { 1.0f,1.0f,1.0f,1.0f };
	directionalLightData->direction = { 0.0f,-1.0f,0.0f };
	directionalLightData->intensity = 1.0f;
}

void Light::ImGui(const char* Title)
{
	ImGui::Begin(Title);
	ImGui::SliderFloat3("LightColor", &directionalLightData->color.x, 0, 1, "%.3f");
	ImGui::SliderFloat3("Lightpotision", &directionalLightData->direction.x, -10, 10, "%.3f");
	ImGui::End();
}
