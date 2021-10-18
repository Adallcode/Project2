#pragma once

#include <vector>

#include "Collision.h"

class PhysicEngine
{
public:
	PhysicEngine();
	~PhysicEngine();

	void AddBox(class BoxComponent* box);
	void RemoveBox(class BoxComponent* box);

	bool SegmentCast(const LineSegment& l, class Actor ** actor);

private:
	std::vector<class BoxComponent*> mBox;
};

