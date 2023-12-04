#include"Scenes/State/GameTitleState.h"

void GameTitleState::Initialize()
{

}

void GameTitleState::Update()
{
	time++;
	if (time >= 60) {
		StateNo = 1;
	}
}

void GameTitleState::Draw()
{

}
