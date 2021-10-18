#pragma once
#include "Actor.h"

#include <string>


class BirdActor :
	public Actor
{
public:
	BirdActor(class Game * game);
	~BirdActor();

	void UpdateActor(float dalta)override;

	std::string Str()const { return "Bird"; }

private:
	static int mDeadCounter;

	//The amount of time that can the Birds reach the floor to end the game
	const int mMaxTimeReachFloor;

};

