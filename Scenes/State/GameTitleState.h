#pragma once
#include"IgameState.h"

class GameTitleState :public GameState
{
public:
	void Initialize();
	void Update();
	void Draw();

private:
	int time;
};
