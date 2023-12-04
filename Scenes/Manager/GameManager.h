#pragma once
#include"WinApp.h"
#include"DirectXCommon.h"
#include"MyEngine.h"
#include"Mesh.h"
#include"TextureManager.h"
#include"Light.h"
#include"ImGuiManager.h"
#include"Scenes/State/GameTitleState.h"
#include"Scenes/State/GamePlayState.h"
#include"Scenes/State/GameClearState.h"
#include"Scenes/State/IgameState.h"
#include"Audio.h"
#include"Input.h"
#include"GlobalVariables.h"
#include "Base/Renderer/Renderer.h"

class GameManager
{
public:
	enum GameStateNo {
		TITLE,
		PLAY,
		CLEAR,
		GameStateMax
	};

	void Run();

private:

	//Base
	MyEngine* myEngine = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* directX = nullptr;
	TextureManager* textureManager = nullptr;

	std::unique_ptr<Renderer> renderer_ = nullptr;

	ImGuiManager* imGuiManager = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;

	Light* light = nullptr;

	MSG msg{};
	//State
	std::unique_ptr<GameState>state[GameStateMax];
	Vector4 ClearColor{ 0.1f,0.25f,0.5f,1.0f };

	int currentSceneNum_;
	int prevSceneNum_;

	void Initialize();
	void Gameloop();
	void Release();
};


