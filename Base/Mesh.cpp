#include "Mesh.h"
void Mesh::Initialize()
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	vertexResource = directX_->CreateBufferResource(sizeof(VertexData)*3);
	MakeVertexBufferView();
	vertexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//左下
	vertexData[0].position = { -0.5f,0.0f,0.0f,1.0f };
	vertexData[0].texcoord = { 0.0f,1.0f };
	//上
	vertexData[1].position = { 0.0f,1.0f,0.0f,1.0f };
	vertexData[1].texcoord = { 0.5f,0.0f };
	//右下
	vertexData[2].position = { 0.5f,0.0f,0.0f,1.0f };
	vertexData[2].texcoord = { 1.0f,1.0f };
	
	materialResource = directX_->CreateBufferResource(sizeof(Material));
	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	materialData->color = color_;
	materialData->enableLighting = false;
	materialData->uvTransform = CreateIdentity4x4();
}

void Mesh::Draw(const WorldTransform& transform, const ViewProjection& viewProjection, const uint32_t textureHandle)
{
	
	Matrix4x4 uvTransformMatrix = MakeScaleMatrix(uvTranformTriAngle.scale);
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeRotateZMatrix(uvTranformTriAngle.rotate.z));
	uvTransformMatrix = Multiply(uvTransformMatrix, MakeTranslateMatrix(uvTranformTriAngle.translate));
	materialData->uvTransform = uvTransformMatrix;
	
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//matWorld
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transform.constBuff_->GetGPUVirtualAddress());
	//ViewProjection
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(4, viewProjection.constBuff_->GetGPUVirtualAddress());
	//colorとuvTransform
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResource.Get()->GetGPUVirtualAddress());
	//texture
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(textureHandle));

	directX_->GetcommandList()->DrawInstanced(3, 1, 0, 0);
}

void Mesh::MakeVertexBufferView()
{
	vertexBufferView.BufferLocation = vertexResource.Get()->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 3;
	vertexBufferView.StrideInBytes = sizeof(VertexData);
}


