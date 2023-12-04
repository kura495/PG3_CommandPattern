#pragma once

#include "Base/DirectXCommon.h"
#include "Manager/PSOManager.h"
#include "PipelineState/Standard/Standard.h"

class Renderer
{
public:
	void Initalize();
	//void Update();
	void Draw(PipelineType Type);

private:
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList = nullptr;
	std::unique_ptr<PSOManager> PSOManager_ = nullptr;
};
