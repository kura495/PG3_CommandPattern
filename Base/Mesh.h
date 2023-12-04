#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "VertexData.h"
#include "Material.h"
#include "MatrixCalc.h"
#include <wrl.h>

class Mesh
{
public:
	void Initialize();
	void Draw(const WorldTransform& transform, const ViewProjection& viewProjection, const uint32_t textureHandle);
private:

	Vector4 color_ = {1.0f,1.0f,1.0f,1.0f};
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	Transform uvTranformTriAngle{
	{1.0f,1.0f,1.0f},
	{0.0f,0.0f,0.0f},
	{0.0f,0.0f,0.0f}
	};

	//バーテックスリソース
	Microsoft::WRL::ComPtr<ID3D12Resource>vertexResource = nullptr;
	VertexData* vertexData = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	Material* materialData = nullptr;

	void MakeVertexBufferView();

};
