#pragma once
#include "Actor.h"


class Player :
	public Actor
{
public:
	Player(class Game *game);


	//Override funtion
	void ActorInput(const Uint8 * key)override;
	void UpdateActor(float delta)override;

private:
	Vector3 mTarget;

	bool mShoot;

	float mTimeToShoot;

	//Helper
	void Shoot(const Quaternion& q);
};

