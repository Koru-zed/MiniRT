#include "../Include/miniRT.h"

bool plane_intersect(t_ray *ray, t_plane *plane)
{
	// First, check if we intersect
	float dDotN = dot(ray.direction, normal);

	if (dDotN == 0.0f)
	{
		// We just assume the ray is not embedded in the plane
		return false;
	}

	// Find point of intersection
	float t = dot(position - intersection.ray.origin, normal)
		/ dDotN;

	if (t <= RAY_T_MIN || t >= intersection.t)
	{
		// Outside relevant range
		return false;
	}

	intersection.t = t;
	intersection.pShape = this;
	intersection.color = color;

	return true;
}