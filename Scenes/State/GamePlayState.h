#pragma once
#include "IgameState.h"
#include "MyEngine.h"
#include "ModelData.h"
#include "Audio.h"
#include "Input.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Light.h"
#include "Sphere.h"
#include "TextureManager.h"
#include "Model.h"
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include "GameObject/Camera/Camera.h"
#include "GameObject/Player/Player.h"
#include "GameObject/Player/LockOn.h"
#include "GameObject/Enemy/Enemy.h"
#include "GameObject/Skydome/Skydome.h"
#include "GameObject/Plane/Plane.h"
#include "GameObject/Plane/MovePlane.h"
#include "GameObject/Goal/Goal.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Base/Utility/CollisionManager.h"
#include "Math_Structs.h"
#include "Base/Math/Quaternion/Quaternion.h"
#include "Base/ParticleSystem/Particle.h"

#include "GameObject/FollowCamera/FollowCamera.h"

class GamePlayState :public GameState
{
public:

	void Initialize();
	void Update();
	void Draw();

private:
	//基本機能ズ
	MyEngine* myEngine = nullptr;
	Camera* camera_ = nullptr;
	TextureManager* textureManager_ = nullptr;	
	Input* input = nullptr;
	Audio* audio=nullptr;
	Light* light_ = nullptr;
	DirectXCommon* DirectX_ = nullptr;
	GlobalVariables* globalVariables = nullptr;
	std::unique_ptr<CollisionManager> collisionManager_;

	std::unique_ptr<FollowCamera> followCamera;
	//
	WorldTransform worldTransform_;
	WorldTransform worldTransform_Sprite;
	ViewProjection viewProjection_;

	//3Dオブジェクトたち
	std::unique_ptr<Player> player;
	std::unique_ptr<LockOn> lockOn_;
	//プレイヤーモデル
	std::unique_ptr<Model> modelFighterBody_ = nullptr;
	std::unique_ptr<Model> modelFighterHead_ = nullptr;
	std::unique_ptr<Model> modelFighterL_arm_ = nullptr;
	std::unique_ptr<Model> modelFighterR_arm_ = nullptr;
	std::unique_ptr<Model> modelFighterWeapon = nullptr;

	std::unique_ptr<Model> modelEnemyBody_ = nullptr;
	std::unique_ptr<Model> modelEnemy_Soul_ = nullptr;

	void AddEnemy(Vector3 Pos);
	std::list<Enemy*> enemies_;

	std::unique_ptr<Skydome> Skydome_;

	std::unique_ptr<Model> model_plane_ = nullptr;
	
	std::unique_ptr<Plane> plane_;
	std::unique_ptr<Plane> plane_2;
	std::unique_ptr<Plane> plane_3;

	std::unique_ptr<Model> model_goal_ = nullptr;
	std::unique_ptr<Goal> goal;

	std::unique_ptr<Model> model_plane_Move_ = nullptr;
	std::unique_ptr<MovePlane> plane_Move_;

	std::unique_ptr<Particle> particle = nullptr;
	int Texture_;
};