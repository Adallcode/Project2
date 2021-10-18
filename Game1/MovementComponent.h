#pragma once
#include "Component.h"


class MovementComponent :
	public Component
{
public:
	MovementComponent(class Actor * owner);

	void Update(float delta)override;

	//Set/Get
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetAngularSpeed(float angular) { mAngular = angular; }
	void SetmRightSpeed(float right) { mRightSpeed = right; }


	float ForwardSpeed()const { return mForwardSpeed; }
	float AngularSpeed()const { return mAngular; }
	float RightSpeed()const { return mRightSpeed; }

private:
	float mForwardSpeed;
	float mAngular;
	float mRightSpeed;
};

