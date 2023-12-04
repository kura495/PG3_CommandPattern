#include"Sprite.h"
void Sprite::Initialize(const Vector4& LeftTop, const Vector4& LeftBottom, const Vector4& RightTop, const Vector4& RightBottom)
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	vertexResource = directX_->CreateBufferResource(sizeof(VertexData) * 4);
	materialResource = directX_->CreateBufferResource(sizeof(Material));

	MakeVertexBufferView();
	indexResource = directX_->CreateBufferResource(sizeof(uint32_t) * 6);
	MakeIndexBufferView();

	vertexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	//左下
	vertexData[0].position = LeftBottom;
	vertexData[0].texcoord = { 0.0f,1.0f };
	//左上
	vertexData[1].position = LeftTop;
	vertexData[1].texcoord = { 0.0f,0.0f };
	//右下
	vertexData[2].position = RightBottom;
	vertexData[2].texcoord = { 1.0f,1.0f };
	//右上
	vertexData[3].position = RightTop;
	vertexData[3].texcoord = { 1.0f,0.0f };

	//インデックスリソースにデータを書き込む
	indexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	//三角形1枚目
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;
	//三角形2枚目
	indexData[3] = 1;
	indexData[4] = 3;
	indexData[5] = 2;

	viewProjection_.Initialize();
	viewProjection_.constMap->view = CreateIdentity4x4();
	viewProjection_.constMap->projection = MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::kClientWidth), float(WinApp::kClientHeight), 0.0f, 100.0f);

}

void Sprite::Draw(const WorldTransform& transform,const uint32_t TextureHandle)
{

	//色の書き込み
	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	materialData->color = color_;
	//ライティングをしない
	materialData->enableLighting = false;
	materialData->uvTransform = CreateIdentity4x4();
	Matrix4x4 uvTransformMatrix = MakeScaleMatrix(uvTranform.scale);
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeRotateZMatrix(uvTranform.rotate.z));
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeTranslateMatrix(uvTranform.translate));
	materialData->uvTransform = uvTransformMatrix;



	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	directX_->GetcommandList()->IASetIndexBuffer(&indexBufferView);
	//WorldTransform
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transform.constBuff_.Get()->GetGPUVirtualAddress());
	//ViewProjection
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(4, viewProjection_.constBuff_->GetGPUVirtualAddress());
	//色とuvTransform
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResource.Get()->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(TextureHandle));

	directX_->GetcommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void Sprite::MakeVertexBufferView()
{
	//リソースの先頭のアドレス
	vertexBufferView.BufferLocation = vertexResource.Get()->GetGPUVirtualAddress();
	//使用する頂点サイズ
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 4;
	//1頂点あたりのアドレス
	vertexBufferView.StrideInBytes = sizeof(VertexData);
}
void Sprite::MakeIndexBufferView()
{
	//リソース先頭アドレス
	indexBufferView.BufferLocation = indexResource.Get()->GetGPUVirtualAddress();
	//使用するインデックスサイズ
	indexBufferView.SizeInBytes = sizeof(uint32_t) * 6;
	//インデックスはuint32_t
	indexBufferView.Format = DXGI_FORMAT_R32_UINT;
}