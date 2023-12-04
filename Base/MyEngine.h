#pragma once

//Base
#include "WinApp.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
//other
#include <numbers>
#include <fstream>

class MyEngine
{
public:

	static MyEngine* GetInstance();
	void Initialize();

private:

	static const int kMaxTexture=10;

	//シングルトン
	MyEngine() = default;
	~MyEngine() = default;
	MyEngine(const MyEngine& obj) = delete;
	MyEngine& operator=(const MyEngine& obj) = delete;

	bool IsusedTextureIndex[kMaxTexture];

	HRESULT hr;
	WinApp* winApp_ = nullptr;
	DirectXCommon* directX_ = nullptr;
	TextureManager* textureManager_ = nullptr;
};