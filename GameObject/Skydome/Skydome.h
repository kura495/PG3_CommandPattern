#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
class Skydome
{
public:
	Skydome();
	~Skydome();

	void Initalize();

	void Update();

	void Draw(ViewProjection ViewProjection_);

private:
	std::unique_ptr<Model> model_;
	WorldTransform worldTransform_;
};

