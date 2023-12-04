#include "MyEngine.h"
#include"Scenes/Manager/GameManager.h"
MyEngine* MyEngine::GetInstance()
{
		static MyEngine instance;
		return &instance;
}

void MyEngine::Initialize()
{
	//Window
	winApp_ = WinApp::GetInstance();
	winApp_->Initialize();
	//DirectX
	directX_ = DirectXCommon::GetInstance();
	directX_->Initialize(winApp_);
	//TextureManager
	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize(directX_);
}



