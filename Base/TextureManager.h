#pragma once
#include "DirectXCommon.h"
#include "externals/DirectXTex/DirectXTex.h"
#include <wrl.h>
#include <array>

class TextureManager
{
public:
	// デスクリプターの数
	static const size_t kMaxTexture = 256;

	/// <summary>
	/// テクスチャ
	/// </summary>
	struct Texture {
		// テクスチャリソース
		Microsoft::WRL::ComPtr<ID3D12Resource> textureResource;
		// シェーダリソースビューのハンドル(CPU)
		CD3DX12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU;
		// シェーダリソースビューのハンドル(CPU)
		CD3DX12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;
		// 名前
		std::string name;
		// 使っているかどうか
		bool IsUsed = false;
	};

	static TextureManager* GetInstance();
	void Initialize(DirectXCommon* directX);
	uint32_t LoadTexture(const std::string& filePath);
	/// <summary>
	/// GPUHandle情報取得
	/// </summary>
	/// <param name="textureHandle">テクスチャハンドル</param>
	const CD3DX12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(uint32_t textureHandle);
private:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager& obj) = delete;
	TextureManager& operator=(const TextureManager& obj) = delete;

	HRESULT hr;
	
	bool IsusedTextureIndex[kMaxTexture];
	DirectXCommon* directX_ = nullptr;
	// テクスチャコンテナ
	std::array<Texture, kMaxTexture> textures_;
	//中間リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource_[kMaxTexture];
	
	DirectX::ScratchImage ImageFileOpen(const std::string& filePath);
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(Microsoft::WRL::ComPtr<ID3D12Device>device, const DirectX::TexMetadata& metadata);
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(Microsoft::WRL::ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);

#pragma region descriptorHeap
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;
#pragma endregion デスクリプタ
};

