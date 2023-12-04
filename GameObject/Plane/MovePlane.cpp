#include "MovePlane.h"

MovePlane::MovePlane(){}
MovePlane::~MovePlane(){}

void MovePlane::Initalize(const std::vector<Model*>& models)
{
	BaseCharacter::Initialize(models);
	worldTransform_.translation_.z = 10.0f;
	worldTransform_.UpdateMatrix();
	BoxCollider::Initialize();
	BoxCollider::SetcollisionMask(~kCollitionAttributeMoveFloor);
	BoxCollider::SetcollitionAttribute(kCollitionAttributeMoveFloor);
	BoxCollider::SetParent(worldTransform_);
	BoxCollider::SetSize({ 10.0f,0.0f,10.0f });
}

void MovePlane::Update()
{
	LinearMoveGimmick();
	BoxCollider::Update(&worldTransform_);
	BaseCharacter::Update();
	if (IsHit == true) {
		player_->SetParent(&worldTransform_);
		IsHit = false;
	}
	else if (IsHit == false) {
		player_->DeleteParent();
	}
	
	
}

void MovePlane::Draw(const ViewProjection& viewProjection)
{
	BaseCharacter::Draw(viewProjection);
}

void MovePlane::OnCollision(uint32_t collisionAttribute)
{
	if (collisionAttribute == kCollitionAttributePlayer) {
		IsHit = true;
	}
	return;
}

void MovePlane::LinearMoveGimmick()
{	
	
	if (linearMoveFlag == true){
		T += kspeedOfT;
		worldTransform_.translation_ = VectorLerp(StartPoint,EndPoint,T);
		if (T >= 1.0f) {
			linearMoveFlag = false;
		}
		else if (T <= 0.0f) {
			linearMoveFlag = false;
		}
	}
	else if (linearMoveFlag == false) {
		AnimeFlame++;
		if (AnimeFlame >= 60.0f) {
			linearMoveFlag = true;
			AnimeFlame = 0.0f;
			kspeedOfT *= -1;
		}
	}

}
