#pragma once
#include "Actor.h"



class Bullet :
	public Actor
{
public:
	Bullet(class Game *game);

	void UpdateActor(float delta)override;


private:


};

