#pragma once
#include "Base/Input/Input.h"

#include "Command/Command.h"


class InputHandler
{
public:
	Command* HandleInput();

	void AssignMoveLeftCommand2PressKeyA();
	void AssignMoveRightCommand2PressKeyD();

private:
	Command* pressKeyD_;
	Command* pressKeyA_;
};