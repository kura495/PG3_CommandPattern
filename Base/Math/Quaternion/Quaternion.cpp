#include "Quaternion.h"

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	Vector3 cross = Cross({ lhs.x,lhs.y,lhs.z }, { rhs.x,rhs.y,rhs.z });
	float dot = Dot({ lhs.x,lhs.y,lhs.z },{ rhs.x,rhs.y,rhs.z });
	result.x = cross.x + rhs.w * lhs.x + lhs.w * rhs.x;
	result.y = cross.y + rhs.w * lhs.y + lhs.w * rhs.y;
	result.z = cross.z + rhs.w * lhs.z + lhs.w * rhs.z;
	result.w = lhs.w * rhs.w - dot;

	return result;
}

Quaternion IdentityQuaternion()
{
	return Quaternion({0.0f,0.0f,0.0f,1.0f});
}

Quaternion Conjugate(const Quaternion& quaternion)
{
	return Quaternion({ quaternion.x*-1.0f,quaternion.y * -1.0f ,quaternion.z * -1.0f ,quaternion.w});
}

float Norm(const Quaternion& quaternion)
{
	return sqrt(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z + quaternion.w * quaternion.w);
}

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

Quaternion Inverse(const Quaternion& quaternion)
{
	Quaternion result;
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
	Quaternion result;
	result.x = axis.x * std::sin(angle/2);
	result.y = axis.y * std::sin(angle/2);
	result.z = axis.z * std::sin(angle / 2);
	result.w = std::cos(angle/2);
	return result;
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	Quaternion fromVector = {vector.x,vector.y,vector.z,0.0f};
	Quaternion conj = Conjugate(quaternion);
	Quaternion rotate = Multiply(quaternion, Multiply(fromVector, conj));
	Vector3 result;
	result.x = rotate.x;
	result.y = rotate.y;
	result.z = rotate.z;

	return result;
}

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	Quaternion result;
	Quaternion Localq0 = q0;
	Quaternion Localq1 = q1;
	//q0とq1の内積
	float dot = Localq0.x * Localq1.x + Localq0.y * Localq1.y + Localq0.z * Localq1.z + Localq0.w * Localq1.w;
	if (dot < 0.0f) {
		//もう片方の回転を利用
		Localq0 = { -q0.x, -q0.y, -q0.z, -q0.w };
		//内積も反転
		dot = -dot;
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
