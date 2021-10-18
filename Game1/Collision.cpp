#include "Collision.h"
#include <array>
#include "SDL.h"

AABB::AABB(const Vector3 & min, const Vector3 & max)
	:mMin(min),
	 mMax(max)
{
}


void AABB::UpdateMinMax(const Vector3 & point)
{
	mMin.x = Math::Min(mMin.x, point.x);
	mMin.y = Math::Min(mMin.y, point.y);
	mMin.z = Math::Min(mMin.z, point.z);

	mMax.x = Math::Max(mMax.x, point.x);
	mMax.y = Math::Max(mMax.y, point.y);
	mMax.z = Math::Max(mMax.z, point.z);
}

void AABB::Rotate(const Quaternion & q)
{
	std::array<Vector3, 8> point;

	point[0] = mMin;

	//Max
	point[1] = Vector3(mMax.x, mMin.y, mMin.z);
	point[2] = Vector3(mMin.x, mMax.y, mMin.z);
	point[3] = Vector3(mMin.x, mMin.y, mMax.z);

	//Min
	point[4] = Vector3(mMin.x, mMax.y, mMax.z);
	point[5] = Vector3(mMax.x, mMin.y, mMax.z);
	point[6] = Vector3(mMax.x, mMax.y, mMin.z);

	point[7] = mMax;

	//Transform each point

	Vector3 p;

	p = Vector3::TransformByQuaternion(point[0], q);

	mMin = p;
	mMax = p;

	for (size_t i = 1; i < point.size(); i++)
	{
		p = Vector3::TransformByQuaternion(point[i], q);
		
		//Update 
		UpdateMinMax(p);
	}

	
}

bool AABB::ContainPoint(const Vector3 & point)const
{
	bool temp =
		(point.x < mMin.x) ||
		(point.y < mMin.y) ||
		(point.z < mMin.z) ||
		(point.x > mMax.x) || //grater
		(point.y > mMax.y) ||
		(point.z > mMax.z);

	return !temp;
}



LineSegment::LineSegment(const Vector3 & start, const Vector3 & end)
	:mStart(start),
	mEnd(end)
{
}

Vector3 LineSegment::Point(float  time)const
{
	return mStart + ( mEnd - mStart ) * time;
}


bool Intersect(const LineSegment & l, const AABB& box, float& t)
{
	std::vector<float> time;

	//Test min x
	Test(l.mStart.x, l.mEnd.x, box.mMin.x, time);
	
	//Test max x
	Test(l.mStart.x, l.mEnd.x, box.mMax.x, time);

	//Test min y
	Test(l.mStart.y, l.mEnd.y, box.mMin.y, time);

	//Test max y
	Test(l.mStart.y, l.mEnd.y, box.mMax.y, time);

	//Test min z
	Test(l.mStart.z, l.mEnd.z, box.mMin.z, time);

	//Test max z
	Test(l.mStart.z, l.mEnd.z, box.mMax.z, time);

	//Sort the vector 
	std::sort(time.begin(), time.end());

	Vector3 p;

	for (auto t1 : time)
	{
		p = l.Point(t1);

		if (box.ContainPoint(p))
		{
			//Return a value later
			t = t1;
			return true;
		}
	}

	return false;
}

void Test(const float& start, const float& end, float boxAxis, std::vector<float>& time)
{
	float denom = end - start;

	//If the denom is near to 0 cant make a division
	if (Math::NearZero(denom))
	{
		return;
	}

	float num = -start + boxAxis;

	float t = num / denom;

	//Time must be within 0-1
	if (t >= 0.0f && t <= 1.0f)
	{
		time.push_back(t);
	}
}
