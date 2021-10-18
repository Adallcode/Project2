#include "PhysicEngine.h"

#include "BoxComponent.h"

#include "Actor.h"


PhysicEngine::PhysicEngine()
{
}

PhysicEngine::~PhysicEngine()
{
	//Clear the box vector because when this destructor is called wont have any components
	mBox.clear();
}

void PhysicEngine::AddBox(BoxComponent * box)
{
	mBox.push_back(box);
}

void PhysicEngine::RemoveBox(BoxComponent * box)
{
	auto it = std::find(mBox.begin(), mBox.end(), box);

	if (it != mBox.end())
	{
		mBox.erase(it);
	}
}

bool PhysicEngine::SegmentCast(const LineSegment & l, Actor ** actor)
{
	bool result = false;
	
	float t;
	float smaller = Math::Infinity;

	
	for (auto b : mBox)
	{
		
		if (Intersect(l, b->WorldBox(), t))
		{
			
			if (t < smaller)
			{
				smaller = t;
				*actor = b->Owner();
				result = true;
				
			}
		}
	}

	return result;
}
