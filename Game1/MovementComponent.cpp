#include "MovementComponent.h"
#include "Actor.h"

#include "Math.h"

MovementComponent::MovementComponent(Actor * owner)
	:Component(owner),
	mForwardSpeed(0.0f),
	mAngular(0.0f),
	mRightSpeed(0.0f)
{
}

void MovementComponent::Update(float delta)
{

	if (!Math::NearZero(mAngular) )
	{
		Quaternion rot = Owner()->QRotation();

		float angle = mAngular * delta;

		rot = Quaternion::Concatenate(rot, Quaternion(Vector3::UnitZ, angle));

		Owner()->SetQRotation(rot);
	}

	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mRightSpeed))
	{
		Vector3 temp = Owner()->Position();

		temp += Owner()->Forward3() * mForwardSpeed * delta;

		temp += Owner()->RightForward() * mRightSpeed * delta;

		Owner()->SetPosition(temp);
	}
}
