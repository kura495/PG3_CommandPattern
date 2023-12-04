#pragma once
#include "Base/Utility/BoxCollider.h"
#include "GameObject/BaseCharacter/BaseCharacter.h"
class Weapon : public BaseCharacter, public BoxCollider
{
public:
	void Initialize(const std::vector<Model*>& models) override;
	void Update() override;
	void Draw(const ViewProjection& viewProjection) override;

	void RootInit();
	void AttackInit();
	void SetParent(const WorldTransform& parent);

	void OnCollision(uint32_t collisionAttribute)override;



private:

};
