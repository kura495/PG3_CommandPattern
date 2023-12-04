#include "BoxCollider.h"

void BoxCollider::Initialize()
{
	world_.Initialize();
	Collider::SetId(ColliderType::Box);
	
}

void BoxCollider::Update(const WorldTransform* world)
{
	//小さいポイントの設定
	aabb_.min.x = center.x - range_.x / 2 + world->GetTranslateFromMatWorld().x;
	aabb_.min.y = center.y - range_.y / 2 + world->GetTranslateFromMatWorld().y;
	aabb_.min.z = center.z - range_.z / 2 + world->GetTranslateFromMatWorld().z;
	//大きいポイントの設定
	aabb_.max.x = center.x + range_.x / 2 + world->GetTranslateFromMatWorld().x;
	aabb_.max.y = center.y + range_.y / 2 + world->GetTranslateFromMatWorld().y;
	aabb_.max.z = center.z + range_.z / 2 + world->GetTranslateFromMatWorld().z;
}

