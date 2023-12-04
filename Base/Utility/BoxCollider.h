#pragma once

#include "Base/Math/Struct/Vector3.h"
#include "Base/WorldTransform.h"
#include "Collider.h"

struct AABB {
	Vector3 min;//一番小さいポイント
	Vector3 max;//一番大きいポイント
};

class BoxCollider : public Collider
{
public:

	void Initialize();
	void Update(const WorldTransform* Parent);
	//void Draw();
	
	//virtual void OnCollision(uint32_t collisionAttribute) = 0;

	///worldの親を設定
	void SetParent(const WorldTransform& Parent) { world_ = Parent; }
	
	void SetSize(Vector3 range) { range_ = range; }
	AABB GetSize() { return aabb_; }

private:
	/// <summary>
	/// x,y,zそれぞれの幅
	/// </summary>
	Vector3 range_;
	/// <summary>
	/// 原点
	/// </summary>
	WorldTransform world_;
	/// <summary>
	/// 箱の大きさ
	/// </summary>
	AABB aabb_ = {};
	/// <summary>
	/// 箱の中心
	/// </summary>
	Vector3 center = {0.0f,0.0f,0.0f};
};
