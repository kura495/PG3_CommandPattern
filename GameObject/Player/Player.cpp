#include "Player.h"

void Player::Init()
{
	model_ = Model::CreateModelFromObj("resources/Cube","Cube.obj");
	world_.Initialize();
}

void Player::Update()
{
	world_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(world_,viewProjection);
}

void Player::MoveRight()
{
	this->world_.translation_.x += this->speed_;
}

void Player::MoveLeft()
{
	this->world_.translation_.x -= this->speed_;
}
