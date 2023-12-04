#include "PSOManager.h"

PSOManager* PSOManager::GetInstance()
{
	static PSOManager instance;
	return &instance;
}

void PSOManager::Initalize()
{
ShaderCompiler* shaderCompiler = ShaderCompiler::GetInstance();
		shaderCompiler->Initalize();

	std::unique_ptr<Standard> standard = std::make_unique<Standard>();
	standard->Initalize();
	AddPipeline(standard->GetPSO(),PipelineType::Standerd);
}
