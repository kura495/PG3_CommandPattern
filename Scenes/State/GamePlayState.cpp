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

	viewProjection. Initialize();

	//
	inputHandler_ = new InputHandler();
	inputHandler_->AssignMoveLeftCommand2PressKeyA();
	inputHandler_->AssignMoveRightCommand2PressKeyD();

	player_ = std::make_unique<Player>();
	player_->Init();

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
	
	command_ = inputHandler_->HandleInput();

	if (this->command_) {
		command_->Exec(*player_);
	}

	player_->Update();


}

void GamePlayState::Draw()
{
	//3Dモデル描画ここから

	player_->Draw(viewProjection);

	//3Dモデル描画ここまで	


	//Sprite描画ここから


	//Sprite描画ここまで
	
	//描画ここまで
}

