#pragma once
#include "MatrixCalc.h"
#include "VectorCalc.h"
#include "Transform.h"
#include "Math_Structs.h"
#include "ImGuiManager.h"
#include "Input.h"

class Camera
{
public:
	void Initialize(int32_t kClientWidth, int32_t kClientHeight);
	void Update();
	const Matrix4x4& GetWorldMatrix() const { return transformationMatrixData; }
#ifdef _DEBUG
	void DebugCamera(bool Flag) {
		DebucCameraFlag = Flag;
}
#endif // DEBUG

private:
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation_ = { 0,0,0 };
	// 累積回転行列
	Matrix4x4 matRot_;
	Vector3 GetmatRot();
	// ローカル座標
	Vector3 translation_ = { 0,2,-5 };
	//　ビュー行列
	Matrix4x4 ViewMatrix;
	// 射影行列
	Matrix4x4 ProjectionMatrix;
	Matrix4x4 worldMatrix;
	Input* input = nullptr;
	//FOVY
	float FOV = 45.0f;
	
	int32_t kClientWidth_;
	int32_t kClientHeight_;
	Matrix4x4 transformationMatrixData;
#ifdef _DEBUG
	bool DebucCameraFlag = false;
	void DebugCameraMove();
#endif // DEBUG

};

