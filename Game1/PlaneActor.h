#pragma once
#include "Actor.h"

class PlaneActor :
	public Actor
{
public:
	PlaneActor(class Game *game);

private:
	class BoxComponent * mBox;
};

