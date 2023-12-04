#include "Math/MatrixCalc.h"
#include <limits>

Matrix4x4 CreateIdentity4x4()
{
	Matrix4x4 result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	return result;
}
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	result.m[0][0] = m1.m[0][0] + m2.m[0][0];
	result.m[0][1] = m1.m[0][1] + m2.m[0][1];
	result.m[0][2] = m1.m[0][2] + m2.m[0][2];
	result.m[0][3] = m1.m[0][3] + m2.m[0][3];

	result.m[1][0] = m1.m[1][0] + m2.m[1][0];
	result.m[1][1] = m1.m[1][1] + m2.m[1][1];
	result.m[1][2] = m1.m[1][2] + m2.m[1][2];
	result.m[1][3] = m1.m[1][3] + m2.m[1][3];

	result.m[2][0] = m1.m[2][0] + m2.m[2][0];
	result.m[2][1] = m1.m[2][1] + m2.m[2][1];
	result.m[2][2] = m1.m[2][2] + m2.m[2][2];
	result.m[2][3] = m1.m[2][3] + m2.m[2][3];

	result.m[3][0] = m1.m[3][0] + m2.m[3][0];
	result.m[3][1] = m1.m[3][1] + m2.m[3][1];
	result.m[3][2] = m1.m[3][2] + m2.m[3][2];
	result.m[3][3] = m1.m[3][3] + m2.m[3][3];

	return result;
}
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
		m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
		m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
		m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
		m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
		m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
		m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
		m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
		m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
		m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
		m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
		m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
		m1.m[2][3] * m2.m[3][3];

	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
		m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
		m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
		m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
		m1.m[3][3] * m2.m[3][3];

	return result;
}
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result = {
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	return result;
}
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,std::cos(radian),std::sin(radian),0.0f,
		0.0f,-std::sin(radian),std::cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {
		std::cos(radian), 0.0f, -std::sin(radian), 0.0f,
		0.0f,1.0f, 0.0f, 0.0f,
		std::sin(radian), 0.0f, std::cos(radian),  0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };
	return result;
}
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {
		std::cos(radian),std::sin(radian),0.0f,0.0f,
		-std::sin(radian),std::cos(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f };
	return result;
}
Matrix4x4 MakeRotateMatrix(Vector3 rotation)
{
	Matrix4x4 result;
	result = CreateIdentity4x4();
	result = Multiply(MakeRotateXMatrix(rotation.x),Multiply(MakeRotateYMatrix(rotation.y),MakeRotateZMatrix(rotation.z)));
	return result;
}
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion)
{
	Matrix4x4 result;
	
	result.m[0][0] = (quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	result.m[0][1] = 2.0f * ((quaternion.x * quaternion.y) + (quaternion.w * quaternion.z));
	result.m[0][2] = 2.0f * ((quaternion.x * quaternion.z) - (quaternion.w * quaternion.y));
	result.m[0][3] = 0.0f;

	result.m[1][0] = 2.0f * ((quaternion.x * quaternion.y) - (quaternion.w * quaternion.z));
	result.m[1][1] = (quaternion.w * quaternion.w) - (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	result.m[1][2] = 2.0f * ((quaternion.y * quaternion.z) + (quaternion.w * quaternion.x));
	result.m[1][3] = 0.0f;

	result.m[2][0] = 2.0f * ((quaternion.x * quaternion.z) + (quaternion.w * quaternion.y));
	result.m[2][1] = 2.0f * ((quaternion.y * quaternion.z) - (quaternion.w * quaternion.x));
	result.m[2][2] = (quaternion.w * quaternion.w) - (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.x, translate.y, translate.z, 1.0f,
	};
	return result;
}
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 Scaleresult = MakeScaleMatrix(scale);
	Matrix4x4 Rotateresult = MakeRotateMatrix(rotate);
	Matrix4x4 Transformresult = MakeTranslateMatrix(translate);
	Matrix4x4 result = Multiply(Scaleresult, Multiply(Rotateresult, Transformresult));

	return result;
}
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Quaternion& rotate, const Vector3& translate) {
	Matrix4x4 Scaleresult = MakeScaleMatrix(scale);
	Matrix4x4 Rotateresult = MakeRotateMatrix(rotate);
	Matrix4x4 Transformresult = MakeTranslateMatrix(translate);
	Matrix4x4 result = Multiply(Scaleresult, Multiply(Rotateresult, Transformresult));

	return result;
}
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Quaternion& quaternion, const Vector3& translate) {
	Matrix4x4 Scaleresult = MakeScaleMatrix(scale);
	Matrix4x4 Rotateresult = MakeRotateMatrix(rotate);
	Matrix4x4 Matquaternion = MakeRotateMatrix(quaternion);
	Rotateresult = Multiply(Rotateresult, Matquaternion);
	Matrix4x4 Transformresult = MakeTranslateMatrix(translate);
	Matrix4x4 result = Multiply(Multiply(Scaleresult, Rotateresult), Transformresult);

	return result;
}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	Vector3 cross = Cross({ lhs.x,lhs.y,lhs.z }, { rhs.x,rhs.y,rhs.z });
	float dot = Dot({ lhs.x,lhs.y,lhs.z }, { rhs.x,rhs.y,rhs.z });
	result.x = cross.x + rhs.w * lhs.x + lhs.w * rhs.x;
	result.y = cross.y + rhs.w * lhs.y + lhs.w * rhs.y;
	result.z = cross.z + rhs.w * lhs.z + lhs.w * rhs.z;
	result.w = lhs.w * rhs.w - dot;

	return result;
}
Quaternion IdentityQuaternion()
{
	return Quaternion({ 0.0f,0.0f,0.0f,1.0f });
}
Quaternion Conjugate(const Quaternion& quaternion)
{
	return Quaternion({ quaternion.x * -1.0f,quaternion.y * -1.0f ,quaternion.z * -1.0f ,quaternion.w });
}
float Norm(const Quaternion& quaternion)
{
	return sqrt(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z + quaternion.w * quaternion.w);
}
Quaternion Inverse(const Quaternion& quaternion)
{
	Quaternion result{};
	float norm = Norm(quaternion);
	norm = norm * norm;
	Quaternion conj = Conjugate(quaternion);
	if (norm != 0.0f) {
		result.x = conj.x / norm;
		result.y = conj.y / norm;
		result.z = conj.z / norm;
		result.w = conj.w / norm;
	}
	return result;
}
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	Quaternion result = IdentityQuaternion();

	float halfAngle = angle / 2.0f;
	float sin = std::sin(halfAngle);

	result.x = axis.x * sin;
	result.y = axis.y * sin;
	result.z = axis.z * sin;
	result.w = std::cos(halfAngle);

	return result;
}
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	Quaternion fromVector = { vector.x,vector.y,vector.z,0.0f };
	Quaternion conj = Conjugate(quaternion);
	Quaternion rotate = Multiply(quaternion, Multiply(fromVector, conj));
	Vector3 result;
	result.x = rotate.x;
	result.y = rotate.y;
	result.z = rotate.z;

	return result;
}
Quaternion Lerp(const Quaternion& q0, const Quaternion& q1,float t) {
	Quaternion result;
	result.x = q1.x - q0.x;
	result.y = q1.y - q0.y;
	result.z = q1.z - q0.z;
	result.w = q1.w - q0.w;
	result.x = q1.x + t * result.x;
	result.y = q1.y + t * result.y;
	result.z = q1.z + t * result.z;
	result.w = q1.w + t * result.w;
	return result;
}
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	Quaternion result;
	Quaternion Localq0 = Normalize(q0);
	Quaternion Localq1 = Normalize(q1);
	//q0とq1の内積
	float dot = Localq0.x * Localq1.x + Localq0.y * Localq1.y + Localq0.z * Localq1.z + Localq0.w * Localq1.w;
	if (dot < 0.0f) {
		//もう片方の回転を利用
		Localq0 = { -Localq0.x, -Localq0.y, -Localq0.z, -Localq0.w };
		//内積も反転
		dot = -dot;
	}
	if (dot >= 1.0f - std::numeric_limits<float>::epsilon())
	{
		result.x = (1.0f - t) * Localq0.x + t * Localq1.x;
		result.y = (1.0f - t) * Localq0.y + t * Localq1.y;
		result.z = (1.0f - t) * Localq0.z + t * Localq1.z;
		result.w = (1.0f - t) * Localq0.w + t * Localq1.w;
		return result;
	}
	//なす角を求める
	float theta = std::acos(dot);

	float scale0 = std::sin((1 - t) * theta) / std::sin(theta);
	float scale1 = std::sin(t * theta) / std::sin(theta);
	result.x = scale0 * Localq0.x + scale1 * Localq1.x;
	result.y = scale0 * Localq0.y + scale1 * Localq1.y;
	result.z = scale0 * Localq0.z + scale1 * Localq1.z;
	result.w = scale0 * Localq0.w + scale1 * Localq1.w;

	return result;
}
//正規化したQuaternionを返す
Quaternion Normalize(const Quaternion& quaternion)
{
	Quaternion result{};
	float norm = Norm(quaternion);
	if (norm != 0.0f) {
		result.x = quaternion.x / norm;
		result.y = quaternion.y / norm;
		result.z = quaternion.z / norm;
		result.w = quaternion.w / norm;
	}
	return result;
}
//VectorからQuaternionを作る
//Quaternion MakeFromVector(const Vector3& rotation, const Vector3& up)
//{
//	return Quaternion();
//}


float det(const Matrix4x4& m)
{
	return float(
		m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] //3行目
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] //6行目
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] //9行目
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] //12行目
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] //15行目
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] //18行目
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] //21行目
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0] //24行目
		);
}
Matrix4x4 Inverse(const Matrix4x4& m)
{
	Matrix4x4 result;
	float resultDet = det(m);
	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) / resultDet;
	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) / resultDet;
	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) / resultDet;
	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) / resultDet;

	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
		+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) / resultDet;
	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) / resultDet;
	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
		+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) / resultDet;
	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) / resultDet;

	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) / resultDet;
	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) / resultDet;
	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) / resultDet;
	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) / resultDet;

	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]
		+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) / resultDet;
	result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) / resultDet;
	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]
		+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) / resultDet;
	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) / resultDet;
	return result;
}
Matrix4x4 MakePerspectiveFovMatrix(float FovY, float aspectRatio, float nearClip, float farClip)
{
	FovY = FovY * ((float)std::numbers::pi / 180);

	Matrix4x4 result = {
	cot(FovY / 2) / aspectRatio,0,0,0,
	0,cot(FovY / 2),0,0,
	0,0,farClip / (farClip - nearClip),1,
	0,0,(-nearClip * farClip) / (farClip - nearClip),0
	};
	return result;
}
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result = {
	width / 2,0,0,0,
	0,-(height / 2),0,0,
	0,0,maxDepth - minDepth,0,
	left + (width / 2),top + (height / 2),minDepth,1
	};
	return result;
}
float cot(float top)
{
	float result = 1 / tan(top);
	return result;
}
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farCcip)
{
	Matrix4x4 result;
	float dx = right - left;
	float dy = top - bottom;
	float dz = farCcip - nearClip;
	result = {
		2.0f / dx,0.0f,0.0f,0.0f,
		0.0f,2.0f / dy,0.0f,0.0f,
		0.0f,0.0f,-2.0f / dz,0.0f,
		-((right + left) / dx),-((top + bottom) / dy),-((farCcip + nearClip) / dz),1.0f
	};
	return result;
}
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	return Vector3(
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	);
}
Vector3 GetXAxis(Matrix4x4 matrix)
{
	return Vector3(matrix.m[0][0], matrix.m[0][1], matrix.m[0][2]);
}
Vector3 GetYAxis(Matrix4x4 matrix)
{
	return Vector3(matrix.m[1][0], matrix.m[1][1], matrix.m[1][2]);
}
Vector3 GetZAxis(Matrix4x4 matrix)
{
	return Vector3(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
}
Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to)
{
	Matrix4x4 result;
	Vector3 cross = Cross(from, to);
	Vector3 n = Normalize(Cross(from, to));
	// u = -v のとき　つまり反転してしまった時
	if (from.x == -to.x && from.y == -to.y && from.z == -to.z) {
		if (from.x != 0.0f || from.y != 0.0f) {
			n = { from.y,-from.x,0.0f };
		}
		else if (from.x != 0.0f || from.z != 0.0f) {
			n = { from.z,0.0f,-from.x };
		}
	}

	float costhata = Dot(from,to);
	float sinthata = Length(cross);
	result.m[0][0] = (n.x * n.x) * (1 - costhata) + costhata;
	result.m[0][1] = (n.x * n.y) * (1 - costhata) + n.z * sinthata;
	result.m[0][2] = (n.x * n.z) * (1 - costhata) - n.y * sinthata;
	result.m[0][3] = 0;

	result.m[1][0] = (n.x * n.y) * (1 - costhata) - n.z * sinthata;
	result.m[1][1] = (n.y * n.y) * (1 - costhata) + costhata;
	result.m[1][2] = (n.y * n.z) * (1 - costhata) + n.x * sinthata;
	result.m[1][3] = 0;

	result.m[2][0] = (n.x * n.z) * (1 - costhata) + n.y * sinthata;
	result.m[2][1] = (n.y * n.z) * (1 - costhata) - n.x * sinthata;
	result.m[2][2] = (n.z * n.z) * (1 - costhata) + costhata;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Matrix4x4 result;

	result.m[0][0] = (axis.x * axis.x) * (1 - cos(angle)) + cos(angle);
	result.m[0][1] = (axis.x * axis.y) * (1 - cos(angle)) + axis.z * sin(angle);
	result.m[0][2] = (axis.x * axis.z) * (1 - cos(angle)) - axis.y * sin(angle);
	result.m[0][3] = 0;

	result.m[1][0] = (axis.x * axis.y) * (1 - cos(angle)) - axis.z * sin(angle);
	result.m[1][1] = (axis.y * axis.y) * (1 - cos(angle)) + cos(angle);
	result.m[1][2] = (axis.y * axis.z) * (1 - cos(angle)) + axis.x * sin(angle);
	result.m[1][3] = 0;

	result.m[2][0] = (axis.x * axis.z) * (1 - cos(angle)) + axis.y * sin(angle);
	result.m[2][1] = (axis.y * axis.z) * (1 - cos(angle)) - axis.x * sin(angle);
	result.m[2][2] = (axis.z * axis.z) * (1 - cos(angle)) + cos(angle);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}


