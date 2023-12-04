#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Light.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "VertexData.h"
#include "Material.h"
#include "MatrixCalc.h"
#include <wrl.h>
#include <numbers>

class Sphere
{
public:

	void Initialize();
	void Draw(const WorldTransform& transform, const ViewProjection& viewProjection, const uint32_t& TextureHandle);

private:
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	Light* light_ = nullptr;
	//分割数
	const int kSubdivision = 16;
	//どのライトを使うか
	int32_t lightFlag = Lighting::NotDo;
	//頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource = nullptr;
	//頂点データ
	VertexData* vertexData = nullptr;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	//マテリアルデータ
	Material* materialData = nullptr;
	//色
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	//インデックスリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource = nullptr;
	//インデックスデータ
	uint32_t* indexData = nullptr;
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};

	void MakeVertexBufferView();
	void MakeIndexBufferView();
	
};
