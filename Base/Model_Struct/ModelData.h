#pragma once
#include "VertexData.h"
#include "Material.h"
#include <vector>

struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
	int TextureIndex;
};