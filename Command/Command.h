#pragma once
#include "GameObject/Player/Player.h"

class Player;

class Command
{
public:
	virtual ~Command() {};
	virtual void Exec(Player& player) = 0;
};
class MoveRightCommand : public Command
{
public:
	void Exec(Player& player)override;
};
class MoveLeftCommand : public Command
{
public:
	void Exec(Player& player)override;
};