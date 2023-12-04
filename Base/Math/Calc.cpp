#include "Calc.h"

float Lerp(float a,float b, float t) {
	float result;

	result = a + b * t;

	return result;
}
float LerpShortAngle(float a, float b, float t)
{
	//角度差分を求める
	float diff = b - a;
	diff = std::fmod(diff, 2 * (float)std::numbers::pi);
	if (diff < 2 * -(float)std::numbers::pi) {
		diff += 2 * (float)std::numbers::pi;
	}
	else if (diff >= 2 * (float)std::numbers::pi) {
		diff -= 2 * (float)std::numbers::pi;
	}

	diff = std::fmod(diff, 2 * (float)std::numbers::pi);
	if (diff < -(float)std::numbers::pi) {
		diff += 2 * (float)std::numbers::pi;
	}
	else if (diff >= (float)std::numbers::pi) {
		diff -= 2 * (float)std::numbers::pi;
	}

	return Lerp(a,diff,t);
}
