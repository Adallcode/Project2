#include "BoxComponent.h"

#include "Actor.h"
#include "Game.h"
#include "PhysicEngine.h"

BoxComponent::BoxComponent(Actor * owner)
	:Component(owner),
	mObjectBox(Vector3::Zero, Vector3::Zero),
	mWorldBox(Vector3::Zero, Vector3::Zero),
	mShouldRotate(true)
{
	owner->GetGame()->Physic()->AddBox(this);
}

BoxComponent::~BoxComponent()
{
	Owner()->GetGame()->Physic()->RemoveBox(this);
}

void BoxComponent::OnUpdate()
{
	mWorldBox = mObjectBox;

	mWorldBox.mMin *= Owner()->Scale();
	mWorldBox.mMax *= Owner()->Scale();

	//SDL_Log("x: %f   x: %f", mWorldBox.mMin.x, mWorldBox.mMax.x);
	if (mShouldRotate)
	{

		mWorldBox.Rotate(Owner()->QRotation());

	}

	mWorldBox.mMin += Owner()->Position();
	mWorldBox.mMax += Owner()->Position();
	
}

void BoxComponent::Update(float delta)
{
	
}


