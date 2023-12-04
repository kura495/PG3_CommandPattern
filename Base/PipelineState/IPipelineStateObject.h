#pragma once

#include "ShaderCompiler/ShaderCompiler.h"

class IPipelineStateObject
{
public:

	~IPipelineStateObject() {};

	void Initalize() {
		
		ShaderCompile();
		CreateRootSignature();
		CreateInputLayOut();
		CreateBlendState();
		CreateRasterizarState();
		CreatePipelineStateObject();
	}
	virtual void ShaderCompile() = 0;
	virtual void CreateRootSignature() = 0;
	virtual void CreateInputLayOut() = 0;
	virtual void CreateBlendState() = 0;
	virtual void CreateRasterizarState() = 0;
	virtual void CreatePipelineStateObject() = 0;

	PipelineStateObject GetPSO() { return PipelineStateObject_; }

protected:
	HRESULT hr;

	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;

	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

	D3D12_BLEND_DESC blendDesc{};

	D3D12_RASTERIZER_DESC rasterizerDesc{};

	PipelineStateObject PipelineStateObject_;

};
