#include "OBBoxCollider.h"

void OBBoxCollider::Initalize()
{
	Collider::SetId(ColliderType::OBBox);
}

void OBBoxCollider::SetOrientations(Matrix4x4 Matrix)
{
	//X成分
	obb_.orientations[0] = GetXAxis(Matrix);
	obb_.orientations[1] = GetYAxis(Matrix);
	obb_.orientations[2] = GetZAxis(Matrix);

}
