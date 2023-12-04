#pragma once
#include "Math_Structs.h"
#include <stdint.h>
#include <string>

struct Material {
	Vector4 color;
	int32_t enableLighting;
	float padding[3];
	Matrix4x4 uvTransform;
};
struct MaterialData {
	std::string textureFilePath;
};
