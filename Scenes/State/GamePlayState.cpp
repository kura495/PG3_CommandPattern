#include "Scenes/State/GamePlayState.h"

void GamePlayState::Initialize()
{
	//基本機能生成
	camera_ = new Camera();
	camera_->Initialize(1280, 720);
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	light_ = Light::GetInstance();

	DirectX_ = DirectXCommon::GetInstance();

	collisionManager_ = std::make_unique<CollisionManager>();
	//
	//3Dオブジェクト生成

#pragma region player
	player = std::make_unique<Player>();
	modelFighterBody_.reset(Model::CreateModelFromObj("resources/float_Body", "float_Body.obj"));
	modelFighterHead_.reset(Model::CreateModelFromObj("resources/float_Head", "float_Head.obj"));
	modelFighterL_arm_.reset(Model::CreateModelFromObj("resources/float_L_arm", "float_L_arm.obj"));
	modelFighterR_arm_.reset(Model::CreateModelFromObj("resources/float_R_arm", "float_R_arm.obj"));
	modelFighterWeapon.reset(Model::CreateModelFromObj("resources/weapon", "weapon.obj"));
	std::vector<Model*> playerModels = {
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),modelFighterR_arm_.get(),modelFighterWeapon.get()
	};
	player->Initialize(playerModels);
	//ロックオン機能
	lockOn_ = std::make_unique<LockOn>();
	lockOn_->Initalize();
#pragma endregion

#pragma region enemy
	modelEnemyBody_.reset(Model::CreateModelFromObj("resources/Enemy", "Enemy_Body.obj"));
	modelEnemy_Soul_.reset(Model::CreateModelFromObj("resources/Enemy", "Enemy_Soul.obj"));
	AddEnemy({ 10.0f, 0.0f, 20.0f});
	AddEnemy({ 7.0f, 0.0f, 20.0f});
#pragma endregion

	Skydome_ = std::make_unique<Skydome>();
	Skydome_->Initalize();

#pragma region Planes

	model_plane_.reset(Model::CreateModelFromObj("resources/Plane", "Plane.obj"));
	std::vector<Model*> PlaneModels = {
		model_plane_.get() };
	plane_ = std::make_unique<Plane>();
	plane_->Initalize(PlaneModels, { 0.0f,0.0f,0.0f });

	plane_2 = std::make_unique<Plane>();
	plane_2->Initalize(PlaneModels, {0.0f, 0.0f, 30.0f});
	plane_3 = std::make_unique<Plane>();
	plane_3->Initalize(PlaneModels, {10.0f, 0.0f, 20.0f});

	model_plane_Move_.reset(Model::CreateModelFromObj("resources/Plane", "MovePlane.obj"));
	std::vector<Model*> Plane_Move_Models = {
		model_plane_Move_.get() };
	plane_Move_ = std::make_unique<MovePlane>();
	plane_Move_->Initalize(Plane_Move_Models);
	plane_Move_->SetPlayer(player.get());

#pragma endregion

	model_goal_.reset(Model::CreateModelFromObj("resources/Cube", "Cube.obj"));
	std::vector<Model*> model_goal_Models = {
		model_goal_.get() };
	goal = std::make_unique<Goal>();
	goal->Initalize(model_goal_Models);


	viewProjection_.Initialize();
	worldTransform_.Initialize();
	followCamera = std::make_unique<FollowCamera>();
	followCamera->Initalize();
	followCamera->SetTarget(&player->GetWorldTransform());
	player->SetViewProjection(&followCamera->GetViewProjection());

	particle = std::make_unique<Particle>();
	particle->Initalize(10,"resources/circle.png");

	Texture_ = TextureManager::GetInstance()->LoadTexture("resources/reticle.png");
}

void GamePlayState::Update()
{
#ifdef _DEBUG
if (input->IspushKey(DIK_LALT)) {
		camera_->DebugCamera(true);
}
else {
	camera_->DebugCamera(false);
}
#endif // _DEBUG


	player->Update();
	
	for (Enemy* enemy_ : enemies_) {
		enemy_->Update();
	}
	
	
	
	Skydome_->Update();
	plane_->Update();
	plane_2->Update();
	plane_3->Update();
	plane_Move_->Update();
	goal->Update();

	GlobalVariables::GetInstance()->Update();
	followCamera->Update();
	viewProjection_ = followCamera->GetViewProjection();
	lockOn_->Update(enemies_,viewProjection_);

	viewProjection_.UpdateMatrix();
	
	
	
	collisionManager_->AddBoxCollider(player.get());
	for (Enemy* enemy_ : enemies_) {
		collisionManager_->AddBoxCollider(enemy_);
	}

	collisionManager_->AddBoxCollider(plane_.get());
	collisionManager_->AddBoxCollider(plane_2.get());
	collisionManager_->AddBoxCollider(plane_3.get());
	collisionManager_->AddBoxCollider(plane_Move_.get());
	collisionManager_->AddBoxCollider(goal.get());
	collisionManager_->AddBoxCollider(player->GetWeapon());
	collisionManager_->CheckAllCollisions();
	collisionManager_->ClearCollider();

	particle->Update();

}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから
	player->Draw(viewProjection_);
	lockOn_->Draw();
	for (Enemy* enemy_ : enemies_) {
		enemy_->Draw(viewProjection_);
	}
	Skydome_->Draw(viewProjection_);
	plane_->Draw(viewProjection_);
	plane_2->Draw(viewProjection_);
	plane_3->Draw(viewProjection_);
	plane_Move_->Draw(viewProjection_);
	goal->Draw(viewProjection_);
	//3Dモデル描画ここまで	

	particle->PreDraw();
	particle->Draw(viewProjection_);

	//Sprite描画ここから


	//Sprite描画ここまで
	
	//描画ここまで
}

void GamePlayState::AddEnemy(Vector3 Pos)
{
	Enemy* enemy_ = new Enemy();
	std::vector<Model*> EnemyModels = {
		modelEnemyBody_.get(),modelEnemy_Soul_.get() };
	enemy_->Initialize(EnemyModels);
	enemy_->SetPos(Pos);
	enemies_.push_back(enemy_);
}
