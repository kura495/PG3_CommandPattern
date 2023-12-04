#pragma once
#include "Math_Structs.h"
#include "VectorCalc.h"
#include <numbers>
#include <cmath>

Matrix4x4 CreateIdentity4x4();
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 MakeRotateMatrix(Vector3 rotation);
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Quaternion& rotate, const Vector3& translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Quaternion& quaternion, const Vector3& translate);
//Quaternionの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
//単位Quaternionを返す
Quaternion IdentityQuaternion();
//共役Quaternionを返す
Quaternion Conjugate(const Quaternion& quaternion);
//Quaternionのnormを返す
float Norm(const Quaternion& quaternion);
//逆Quaternionを返す
Quaternion Inverse(const Quaternion& quaternion);
//任意軸回転を表すQuaternionの生成
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);
//ベクトルをQuaternionで回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);
//Quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);
Quaternion Lerp(const Quaternion& q0, const Quaternion& q1,float t);
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);
//正規化したQuaternionを返す
Quaternion Normalize(const Quaternion& quaternion);
//Quaternion MakeFromVector(const Vector3& rotation,/*上方向を定義するベクトル*/ const Vector3& up = {0.0f,1.0f,0.0f});
float det(const Matrix4x4& m);
Matrix4x4 Inverse(const Matrix4x4& m);
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float FovY, float aspectRatio, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
//cotangent関数
float cot(float top);

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom,float nearClip,float farCcip);
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
Vector3 GetXAxis(Matrix4x4 matrix);
Vector3 GetYAxis(Matrix4x4 matrix);
Vector3 GetZAxis(Matrix4x4 matrix);
Matrix4x4 DirectionToDirection(const Vector3& from,const Vector3& to);
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);