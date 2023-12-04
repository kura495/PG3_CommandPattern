#include "LockOn.h"


void LockOn::Initalize()
{
	input = Input::GetInstance();
	Texture_ = TextureManager::GetInstance()->LoadTexture("resources/reticle.png");
	lockOnMark_ = std::make_unique<Sprite>();
	Vector4 LeftTop[2] = {
		{ 0.0f,0.0f,0.0f,1.0f },
		{ 360.0f,0.0f,0.0f,1.0f }
	};
	Vector4 LeftBottom[2] = {
		{ 0.0f,64.0f,0.0f,1.0f },
		{ 360.0f,360.0f,0.0f,1.0f }
	};
	Vector4 RightTop[2] = {
		{ 360.0f,0.0f,0.0f,1.0f },
		{ 64.0f,0.0f,0.0f,1.0f }
	};
	Vector4 RightBottom[2] = {
		{ 360.0f,180.0f,0.0f,1.0f },
		{ 64,64,0.0f,1.0f }
	};
	lockOnMark_->Initialize(LeftTop[0], LeftBottom[0], RightTop[1], RightBottom[1]);
	world_.Initialize();
	world_.translation_.x = -3.0f;

}

void LockOn::Update(const std::list<Enemy*>& enemies,const ViewProjection& viewProjection)
{
	input->GetJoystickState(0,joyState);
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		if (!(joyStatePre.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) {
			search(enemies, viewProjection);
		}
	}
	joyStatePre = joyState;
}

void LockOn::Draw()
{
	/*if (target_) {*/
		lockOnMark_->Draw(world_, Texture_);
	
}

void LockOn::search(const std::list<Enemy*>& enemies, const ViewProjection& viewProjection)
{
	//目標
	std::list<std::pair<float, const Enemy*>> targets;
	//全ての敵に対して順にロックオン判定
	for (Enemy* enemy_ : enemies) {
		//敵のロックオン座標取得
		Vector3 positionWorld = enemy_->GetWorldTransform().translation_;

		//ワールド→ビュー座標変換
		Vector3 positionView = VectorTransform(positionWorld,viewProjection.matView);

		if (minDistance_ <= positionView.z && positionView.z <= maxDistance_) {
			//カメラ前方との角度を計算
			float arcTangent = std::atan2(std::sqrt(positionView.x * positionView.x + positionView.y * positionView.y), positionView.z);

			//角度条件チェック(コーンにおさまっているか)
			if (std::abs(arcTangent) <= angleRange_) {
				targets.emplace_back(std::make_pair(positionView.z, enemy_));
			}
		}
	}

	//ロックオン対象をリセット
	target_ = nullptr;
	//targetsが空っぽ出なければ
	if (!targets.empty()) {
		//距離で昇順でソート
		targets.sort([](auto& pair1, auto& pair2) {return pair1.first < pair2.first; });
		//ソートの結果一番近い敵をロックオン対象とする
		target_ = targets.front().second;

	}

}
