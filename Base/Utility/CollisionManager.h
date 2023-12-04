#pragma once
#include "Utility/Collider.h"
#include "Utility/BoxCollider.h"
#include "Utility/OBBoxCollider.h"
#include "Utility/CollisionConfig.h"
#include <list>

class CollisionManager {
public:
	void AddCollider(Collider* collider) { colliders_.push_back(collider); }
	void AddBoxCollider(BoxCollider* collider) { BoxColliders_.push_back(collider); }
	void ClearCollider() {
		colliders_.clear(); BoxColliders_.clear();
	}
	void CheckAllCollisions();

private:
	/// <summary>
	/// コライダー登録用
	/// </summary>
	std::list<Collider*> colliders_;
	/// <summary>
	///　Boxコライダー登録用
	/// </summary>
	std::list<BoxCollider*> BoxColliders_;
	
	//void CheckCollisionCircle(Collider* colliderA, Collider* colliderB);
	void CheckCollisionBox(BoxCollider* colliderA, BoxCollider* colliderB);
	//void CheckCollitionOBBox(OBBoxCollider* colliderA, OBBoxCollider* colliderB);
};
