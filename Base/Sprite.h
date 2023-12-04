#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Transform.h"
#include "VertexData.h"
#include "Material.h"
#include "MatrixCalc.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <wrl.h>

class Sprite
{
public:
	void Initialize(const Vector4& LeftTop, const Vector4& LeftBottom, const Vector4& RightTop, const Vector4& RightBottom);
	void Draw(const WorldTransform& transform, const uint32_t TextureHandle);
	void ImGui(const char* Title);
private:
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource = nullptr;
	VertexData* vertexData = nullptr;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	Material* materialData = nullptr;
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };

	//Index用
	Microsoft::WRL::ComPtr<ID3D12Resource>indexResource = nullptr;
	uint32_t* indexData = nullptr;
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	Transform uvTranform{
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	ViewProjection viewProjection_;

	void MakeVertexBufferView();
	void MakeIndexBufferView();

};
