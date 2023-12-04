#include "VectorCalc.h"

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

float Dot(const Vector3& v1, const Vector3& v2) {
	float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}

float Length(const Vector3& v) {
	float result{};
	result = sqrt(Dot(v, v));
	return result;
}

Vector3 Normalize(const Vector3& v1) {
	Vector3 result{};
	float length = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	if (length != 0.0f) {
		result.x = v1.x / length;
		result.y = v1.y / length;
		result.z = v1.z / length;
	}
	return result;
}
Vector3 VectorLerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;
	if (t < 0) {
		t = (float)std::min(0, 1);
	}
	else if (t > 1) {
		t = (float)std::max(0, 1);
	}

	result.x = v1.x + t * (v2.x - v1.x);
	result.y = v1.y + t * (v2.y - v1.y);
	result.z = v1.z + t * (v2.z - v1.z);

	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return result;
}
Vector3 VectorTransform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float W = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(W != 0.0f);
	result.x /= W;
	result.y /= W;
	result.z /= W;
	return result;
}