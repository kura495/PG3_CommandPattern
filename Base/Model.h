#pragma once
#include "Material.h"
#include "Transform.h"
#include "VertexData.h"
#include "ModelData.h"
#include "TextureManager.h"
#include "Light.h"
#include "ImGuiManager.h"
#include "GlobalVariables.h"
#include "MatrixCalc.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <d3d12.h>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <wrl.h>

class Model
{
public:
	void Initialize(const std::string& directoryPath, const std::string& filename);
	void Draw(const WorldTransform& transform,const ViewProjection& viewProjection);
	void Draw(const WorldTransform& transform,const ViewProjection& viewProjection,uint32_t TextureHundle);
	static Model* CreateModelFromObj(const std::string& directoryPath, const std::string& filename);
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);
	void SetLightMode(Lighting number) { lightFlag = number; };
private:

	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	Light* light_ = nullptr;
	//どのライトを使うか
	int32_t lightFlag = Lighting::harfLambert;

	ModelData modelData_;
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
	
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

};