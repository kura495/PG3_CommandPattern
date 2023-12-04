#include "Model.h"

void Model::Initialize(const std::string& directoryPath, const std::string& filename)
{
	directX_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();
	materialResource = directX_->CreateBufferResource(sizeof(Material));

	modelData_ = LoadObjFile(directoryPath,filename);
	//バッファリソースはLoadObjFileの中で作ってるよ
	vertexResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	std::memcpy(vertexData, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());

	materialResource.Get()->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	
	materialData->uvTransform = CreateIdentity4x4();
}

void Model::Draw(const WorldTransform& transform, const ViewProjection& viewProjection)
{

	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	//matWorld
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transform.constBuff_->GetGPUVirtualAddress());
	//ViewProjection
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(4, viewProjection.constBuff_->GetGPUVirtualAddress());
	//色とuvTransform
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(modelData_.TextureIndex));
	//Light
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(3, light_->GetDirectionalLight()->GetGPUVirtualAddress());

	directX_->GetcommandList()->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);
	materialData->enableLighting = lightFlag;
	materialData->color = color_;
}

void Model::Draw(const WorldTransform& transform, const ViewProjection& viewProjection, uint32_t TextureHundle)
{

	directX_->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点
	directX_->GetcommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	//matWorld
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(1, transform.constBuff_->GetGPUVirtualAddress());
	//ViewProjection
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(4, viewProjection.constBuff_->GetGPUVirtualAddress());
	//色とuvTransform
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//テクスチャ
	directX_->GetcommandList()->SetGraphicsRootDescriptorTable(2, textureManager_->GetGPUHandle(TextureHundle));
	//Light
	directX_->GetcommandList()->SetGraphicsRootConstantBufferView(3, light_->GetDirectionalLight()->GetGPUVirtualAddress());

	directX_->GetcommandList()->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);
	materialData->enableLighting = lightFlag;
	materialData->color = color_;
}

Model* Model::CreateModelFromObj(const std::string& directoryPath, const std::string& filename)
{
	Model* model=new Model();
	model->Initialize(directoryPath,filename);
	return model;
}

ModelData Model::LoadObjFile(const std::string& directoryPath, const std::string& filename)
{
	ModelData modelData;//構築するモデルデータ
	std::vector<Vector4>positions;//位置　vを保存
	std::vector<Vector2>texcoords;//テクスチャ座標　vtを保存
	std::vector<Vector3>normals;//法線　vnを保存
	std::string line;//ファイルから読んだ一行を格納するもの
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());//開けなかったら止める
	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;//先頭の識別子を読む
		if (identifier == "v") {
			Vector4 position;
			s >> position.x >> position.y >> position.z;
			//右手系から左手系へ
			position.z *= -1.0f;
			position.w = 1.0f;
			positions.push_back(position);
		}
		else if (identifier == "vt") {
			Vector2 texcoord;
			s >> texcoord.x >> texcoord.y;
			texcoord.y = 1.0f - texcoord.y;
			texcoords.push_back(texcoord);
		}
		else if (identifier == "vn") {
			Vector3 normal;
			s >> normal.x >> normal.y >> normal.z;
			//右手系から左手系へ
			normal.z *= -1.0f;
			normals.push_back(normal);
		}
		else if (identifier == "f") {
			//面は三角形限定
			VertexData triamgle[3];
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
				std::string vertexDefinition;
				s >> vertexDefinition;
				//頂点の要素へのIndexは「位置/UV/法線」で格納されているので、分解してIndexを取得する
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];
				for (int32_t element = 0; element < 3; ++element) {
					std::string index;
					std::getline(v, index, '/');// /区切りでインデックスを読んでいく
					elementIndices[element] = std::stoi(index);
				}
				Vector4 position = positions[elementIndices[0] - 1];
				Vector2 texcoord = texcoords[elementIndices[1] - 1];
				Vector3 normal = normals[elementIndices[2] - 1];
				//VertexData vertex = { position,texcoord,normal };
				//modelData.vertices.push_back(vertex);
				triamgle[faceVertex] = { position,texcoord,normal };

			}
			modelData.vertices.push_back(triamgle[2]);
			modelData.vertices.push_back(triamgle[1]);
			modelData.vertices.push_back(triamgle[0]);
		}
		else if (identifier == "mtllib") {
			//materialTemplateLibraryファイルの名前を取得する
			std::string materialFilename;
			s >> materialFilename;
			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFilename);
		}
	}
	modelData.TextureIndex = textureManager_->LoadTexture(modelData.material.textureFilePath);
	//頂点リソースを作る
	vertexResource = directX_->CreateBufferResource(sizeof(VertexData) * modelData.vertices.size());
	vertexBufferView.BufferLocation = vertexResource.Get()->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = UINT(sizeof(VertexData) * modelData.vertices.size());
	vertexBufferView.StrideInBytes = sizeof(VertexData);
	return modelData;
}

MaterialData Model::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename)
{
	MaterialData material;//構築するMaterialData
	std::string line;//ファイルから読んだ1行を格納するもの
	std::ifstream file(directoryPath + '/' + filename);//ファイルを開く
	assert(file.is_open());//開けなかったら止める
	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;
		//identifierに応じた処理
		if (identifier == "map_Kd") {
			std::string textureFilename;
			s >> textureFilename;
			//連結してファイルパスにする
			material.textureFilePath = directoryPath + "/" + textureFilename;
		}
	}

	return material;
}
