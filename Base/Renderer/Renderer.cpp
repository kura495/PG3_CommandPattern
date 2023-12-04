#include "Renderer.h"

void Renderer::Initalize()
{
	commandList = DirectXCommon::GetInstance()->GetcommandList();
	PSOManager_ = std::make_unique<PSOManager>();
	PSOManager_->Initalize();

}

void Renderer::Draw(PipelineType Type)
{
	commandList->SetGraphicsRootSignature(PSOManager_->GetRootSignature(Type).Get());
	commandList->SetPipelineState(PSOManager_->GetPipelineState(Type).Get());
}
