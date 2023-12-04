#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Transform.h"
#include "Input.h"
#include "VectorCalc.h"
#include "Base/Utility/BoxCollider.h"
#include "Base/Utility/CollisionConfig.h"

enum modelNumber {
	kModelIndexBody,
	kModelIndexHead,
	kModelIndexL_arm,
	kModelIndexR_arm,
	kModelIndexWeapon
};

class BaseCharacter
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models">モデルデータ配列</param>
	virtual void Initialize(const std::vector<Model*>& models);
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション(参照渡し)</param>
	virtual void Draw(const ViewProjection& viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

protected:
	std::vector<Model*> models_;

	WorldTransform worldTransform_;

private:

};