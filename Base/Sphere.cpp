#include"Sphere.h"

void Sphere::Initialize()
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();

	vertexResource = directX_->CreateBufferResource(sizeof(VertexData) * 4 * kSubdivision * kSubdivision);
	vertexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	materialResource = directX_->CreateBufferResource(sizeof(Material));
	MakeVertexBufferView();

	indexResource = directX_->CreateBufferResource(sizeof(uint32_t) * 6 * kSubdivision * kSubdivision);
	indexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	MakeIndexBufferView();

	//経度分割の1つ分の角度　φ 横
	const float kLonEvery = float(std::numbers::pi) * 2.0f / float(kSubdivision);
	//緯度分割の1つ分の角度　θ 縦
	const float kLatEvery = float(std::numbers::pi) / float(kSubdivision);
	for (int latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(std::numbers::pi) / 2.0f + kLatEvery * latIndex;
		float uvLength = 1.0f / kSubdivision;
		for (int lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			uint32_t Vertexstart = (latIndex * kSubdivision + lonIndex) * 4;
			uint32_t Indexstart = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery;
			float u = float(lonIndex) / float(kSubdivision);
			float v = 1.0f - float(latIndex) / float(kSubdivision);
#pragma region VertexData
			//点A(左下)
			vertexData[Vertexstart].position.x = cos(lat) * cos(lon);
			vertexData[Vertexstart].position.y = sin(lat);
			vertexData[Vertexstart].position.z = cos(lat) * sin(lon);
			vertexData[Vertexstart].position.w = 1.0f;
			vertexData[Vertexstart].texcoord = { u ,v };
			vertexData[Vertexstart].normal.x = vertexData[Vertexstart].position.x;
			vertexData[Vertexstart].normal.y = vertexData[Vertexstart].position.y;
			vertexData[Vertexstart].normal.z = vertexData[Vertexstart].position.z;
			//点B(左上)
			vertexData[Vertexstart + 1].position.x = cos(lat + kLatEvery) * cos(lon);
			vertexData[Vertexstart + 1].position.y = sin(lat + kLatEvery);
			vertexData[Vertexstart + 1].position.z = cos(lat + kLatEvery) * sin(lon);
			vertexData[Vertexstart + 1].position.w = 1.0f;
			vertexData[Vertexstart + 1].texcoord = { u,v - uvLength };
			vertexData[Vertexstart + 1].normal.x = vertexData[Vertexstart + 1].position.x;
			vertexData[Vertexstart + 1].normal.y = vertexData[Vertexstart + 1].position.y;
			vertexData[Vertexstart + 1].normal.z = vertexData[Vertexstart + 1].position.z;
			//点C(右下)
			vertexData[Vertexstart + 2].position.x = cos(lat) * cos(lon + kLonEvery);
			vertexData[Vertexstart + 2].position.y = sin(lat);
			vertexData[Vertexstart + 2].position.z = cos(lat) * sin(lon + kLonEvery);
			vertexData[Vertexstart + 2].position.w = 1.0f;
			vertexData[Vertexstart + 2].texcoord = { u + uvLength,v };
			vertexData[Vertexstart + 2].normal.x = vertexData[Vertexstart + 2].position.x;
			vertexData[Vertexstart + 2].normal.y = vertexData[Vertexstart + 2].position.y;
			vertexData[Vertexstart + 2].normal.z = vertexData[Vertexstart + 2].position.z;
			//点D(右上)
			vertexData[Vertexstart + 3].position.x = cos(lat + kLatEvery) * cos(lon + kLonEvery);
			vertexData[Vertexstart + 3].position.y = sin(lat + kLatEvery);
			vertexData[Vertexstart + 3].position.z = cos(lat + kLatEvery) * sin(lon + kLonEvery);
			vertexData[Vertexstart + 3].position.w = 1.0f;
			vertexData[Vertexstart + 3].texcoord = { u + uvLength,v - uvLength };
			vertexData[Vertexstart + 3].normal.x = vertexData[Vertexstart + 3].position.x;
			vertexData[Vertexstart + 3].normal.y = vertexData[Vertexstart + 3].position.y;
			vertexData[Vertexstart + 3].normal.z = vertexData[Vertexstart + 3].position.z;
#pragma endregion 頂点データ
			//三角形1枚目
			indexData[Indexstart] = Vertexstart;
			indexData[Indexstart + 1] = Vertexstart + 1;
			indexData[Indexstart + 2] = Vertexstart + 2;
			//三角形2枚目
			indexData[Indexstart + 3] = Vertexstart + 1;
			indexData[Indexstart + 4] = Vertexstart + 3;
			indexData[Indexstart + 5] = Vertexstart + 2;
		}
	}
}

void Sphere::Draw(const WorldTransform& transform, const ViewProjection& viewProjection, const uint32_t& TextureHandle)
{
	
	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	//ライティングをする
	materialData->color = color_;
	materialData->enableLighting = lightFlag;
	materialData->uvTransform = CreateIdentity4x4();

	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	directX_->GetcommandList()->IASetIndexBuffer(&indexBufferView);
	//colorとuvTransform
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResource.Get()->GetGPUVirtualAddress());
	//WorldTransform
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transform.constBuff_.Get()->GetGPUVirtualAddress());
	//ViewProjection
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(4, viewProjection.constBuff_->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(TextureHandle));
	//Light
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(3, light_->GetDirectionalLight()->GetGPUVirtualAddress());

	directX_->GetcommandList()->DrawIndexedInstanced(kSubdivision * kSubdivision * 6, 1, 0, 0, 0);
}

void Sphere::MakeVertexBufferView()
{
	//リソースの先頭のアドレス
	vertexBufferView.BufferLocation = vertexResource.Get()->GetGPUVirtualAddress();
	//使用する頂点サイズ
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 4 * kSubdivision * kSubdivision;
	//1頂点あたりのアドレス
	vertexBufferView.StrideInBytes = sizeof(VertexData);
}
void Sphere::MakeIndexBufferView()
{
	//リソース先頭アドレス
	indexBufferView.BufferLocation = indexResource.Get()->GetGPUVirtualAddress();
	//使用するインデックスサイズ
	indexBufferView.SizeInBytes = sizeof(uint32_t) * 6 * kSubdivision * kSubdivision;
	//インデックスはuint32_t
	indexBufferView.Format = DXGI_FORMAT_R32_UINT;
}
