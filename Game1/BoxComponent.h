#pragma once
#include "Component.h"

#include "Collision.h"

class BoxComponent :
	public Component
{
public:
	BoxComponent(class Actor* owner);
	~BoxComponent();

	void OnUpdate()override;
	void Update(float delta)override;

	//Box
	void SetObjectBox(const AABB& box) { mObjectBox = box; }

	AABB WorldBox()const { return mWorldBox; }

	void SetShouldRotate(bool rotate) { mShouldRotate = rotate; }
	bool ShouldRotate()const { return mShouldRotate; }

private:
	AABB mObjectBox;
	AABB mWorldBox;

	bool mShouldRotate;
};

