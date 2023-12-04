#include "InputHandle.h"

Command* InputHandler::HandleInput()
{
	if (Input::GetInstance()->IspushKey(DIK_D)) {
		return pressKeyD_;
	}
	if (Input::GetInstance()->IspushKey(DIK_A)) {
		return pressKeyA_;
	}
	return nullptr;
}

void InputHandler::AssignMoveLeftCommand2PressKeyA()
{
	Command* command = new MoveLeftCommand();
	this->pressKeyA_ = command;
}

void InputHandler::AssignMoveRightCommand2PressKeyD()
{
	Command* command = new MoveRightCommand();
	this->pressKeyD_ = command;
}
