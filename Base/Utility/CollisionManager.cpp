#include "CollisionManager.h"


void CollisionManager::CheckAllCollisions() {
	// リスト内のペアを総当たり
	//std::list<Collider*>::iterator itrA = colliders_.begin();
	//for (; itrA != colliders_.end(); ++itrA) {
	//	// イテレータAからコライダーを取得
	//	Collider* colliderA = *itrA;
	//	// イテレータBはイテレータAの次の要素から回す(重複を避ける)
	//	std::list<Collider*>::iterator itrB = itrA;
	//	itrB++;
	//	for (; itrB != colliders_.end(); ++itrB) {
	//		Collider* colliderB = *itrB;
	//		//円と円
	//		/*if (colliderA->GetId() == ColliderType::Circle && colliderB->GetId() == ColliderType::Circle) {
	//			CheckCollisionCircle(colliderA, colliderB);
	//		}*/
	//		//AABBとAABB
	//	}
	//}
	std::list<BoxCollider*>::iterator BoxitrA = BoxColliders_.begin();
	for (; BoxitrA != BoxColliders_.end(); ++BoxitrA) {
		// イテレータAからコライダーを取得
		BoxCollider* colliderA = *BoxitrA;
		// イテレータBはイテレータAの次の要素から回す(重複を避ける)
		std::list<BoxCollider*>::iterator BoxitrB = BoxitrA;
		BoxitrB++;
		for (; BoxitrB != BoxColliders_.end(); ++BoxitrB) {
			BoxCollider* colliderB = *BoxitrB;
			CheckCollisionBox(colliderA, colliderB);
		}
	}
}

//void CollisionManager::CheckCollisionCircle(Collider * colliderA, Collider * colliderB) {
//	// 判定対象AとBの座標
//	Vector3 posA = { 1.0f,1.0f,1.0f }, posB = {1.0f, 1.0f,1.0f};
//	//posA = colliderA->GetWorldPosition();
//	//posB = colliderB->GetWorldPosition();
//	float Length =(float)sqrt(
//	    (posB.x - posA.x) * (posB.x - posA.x) +
//		(posB.y - posA.y) * (posB.y - posA.y) +
//	    (posB.z - posA.z) * (posB.z - posA.z));
//	// コライダーのフィルターの値でビット演算
//	if ((colliderA->GetcollitionAttribute() & colliderB->GetcollisionMask()) == 0 && (colliderB->GetcollitionAttribute() & colliderA->GetcollisionMask()) == 0) {
//		return;
//	}
//	else if ((colliderA->GetcollitionAttribute() & colliderB->GetcollisionMask()) == 0) {
//		if (Length <= colliderA->GetRadius() + colliderB->GetRadius()) {
//			// コライダーAの衝突時コールバック
//			colliderA->OnCollision(colliderB->GetcollitionAttribute());
//		}
//	}
//	else if ((colliderB->GetcollitionAttribute() & colliderA->GetcollisionMask()) == 0) {
//		if (Length <= colliderA->GetRadius() + colliderB->GetRadius()) {
//			// コライダーBの衝突時コールバック
//			colliderB->OnCollision(colliderA->GetcollitionAttribute());
//		}
//	}
//	else {
//		if (Length <= colliderA->GetRadius() + colliderB->GetRadius()) {
//			// コライダーAの衝突時コールバック
//			colliderA->OnCollision(colliderB->GetcollitionAttribute());
//			// コライダーBの衝突時コールバック
//			colliderB->OnCollision(colliderA->GetcollitionAttribute());
//		}
//	}
//}


//void CollisionManager::CheckCollitionOBBox(OBBoxCollider* colliderA, OBBoxCollider* colliderB)
//{
//	
//}

void CollisionManager::CheckCollisionBox(BoxCollider * colliderA, BoxCollider * colliderB)
{
	// 判定対象AとBの座標
	AABB posA, posB;
	posA = colliderA->GetSize();
	posB = colliderB->GetSize();

	// コライダーのフィルターの値でビット演算
	if ((colliderA->GetcollitionAttribute() & colliderB->GetcollisionMask()) == 0 && (colliderB->GetcollitionAttribute() & colliderA->GetcollisionMask()) == 0) {
		return;
	}

	if ((posA.min.x <= posB.max.x && posA.max.x >= posB.min.x) && //x軸
		(posA.min.y <= posB.max.y && posA.max.y >= posB.min.y) && //y軸
		(posA.min.z <= posB.max.z && posA.max.z >= posB.min.z)    //z軸
		) {
		if ((colliderA->GetcollitionAttribute() & colliderB->GetcollisionMask()) == 0) {
			// コライダーAの衝突時コールバック
			colliderA->OnCollision(colliderB->GetcollitionAttribute());
		}
		else if ((colliderB->GetcollitionAttribute() & colliderA->GetcollisionMask()) == 0) {
			// コライダーBの衝突時コールバック
			colliderB->OnCollision(colliderA->GetcollitionAttribute());
		}
		else {
			// コライダーAの衝突時コールバック
			colliderA->OnCollision(colliderB->GetcollitionAttribute());
			// コライダーBの衝突時コールバック
			colliderB->OnCollision(colliderA->GetcollitionAttribute());
		}
	}

}
