#pragma once

#include <vector>

#include "Math.h"

struct AABB
{
public:
	explicit AABB(const Vector3& min, const Vector3& max);
	AABB();


	void UpdateMinMax(const Vector3& point);
	void Rotate(const Quaternion& q);
	bool ContainPoint(const Vector3& point)const;

	Vector3 mMin;
	Vector3 mMax;
};


struct LineSegment
{
public:
	explicit LineSegment(const Vector3& start, const Vector3& end);
	
	Vector3 Point(float time)const;

	Vector3 mStart;
	Vector3 mEnd;

};


//Some funtions to check collision
bool Intersect(const LineSegment& l, const AABB& box, float& t);

void Test(const float& start, const float& end, float boxAxis, std::vector<float>& time);