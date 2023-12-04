#pragma once
#include <random>
#include <numbers>

#include "DirectXCommon.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Math/MatrixCalc.h"
#include "ModelData.h"
#include "Base/Light.h"

#include "Utility/ImGuiManager.h"

#include "PipeLine/ParticlePipeLine.h"

struct ParticleForGPU {
	Matrix4x4 matWorld;
	Vector3 velocity;
	Vector4 color;
	float lifeTime;
	float currentTime;
	Vector3 translate;
};

class Particle
{
public:

	void Initalize(int particleVolume,const std::string filePath);
	void Initalize(int particleVolume,const std::string filePath,Vector3 Pos);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void PreDraw();

	void SetPos(Vector3 Pos);

private:
	//インスタンスの数
	const uint32_t kNumMaxInstance = 10;
	//生きているインスタンスの数
	uint32_t numInstance = 0;

	ModelData modelData;

	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource>vertexResource = nullptr;
	VertexData* vertexData = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = nullptr;
	Material* materialData = nullptr;
	//Instancing用にTransformMatrixを複数格納できるResourcesを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> InstancingResource = nullptr;
	WorldTransform InstancingDeta[10];
	ParticleForGPU* particles;

	//パーティクルの数
	int particleVolume_;
	//パーティクルの数分のtransform
	std::vector<WorldTransform> transform_;

	void CreateResources();
	void CreateSRV();

	std::unique_ptr<ParticlePipeLine> Pipeline_;

	D3D12_CPU_DESCRIPTOR_HANDLE instancingSRVHandleCPU;
	D3D12_GPU_DESCRIPTOR_HANDLE instancingSRVHandleGPU;

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);

	const float kDeltaTime = 1.0f / 60.0f;

	//ランダム
	ParticleForGPU MakeNewParticle(std::mt19937& randomEngine);
	Vector4 MakeParticleColor(std::mt19937& randomEngine);
	float MakeParticleLifeTime(std::mt19937& randomEngine);
};

