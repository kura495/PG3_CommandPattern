#pragma once
#include "Base/Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Player
{
public:

	void Init();
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void MoveRight();
	void MoveLeft();

private:
	WorldTransform world_;

	float speed_ = 2.0f;

	Model* model_ = nullptr;

};