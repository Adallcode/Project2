#pragma once

#include "SDL.h"

class Component
{
public:
	Component(class Actor *owner, int updateOrder = 100);
	virtual ~Component();

	//Virtuals
	virtual void ProcessInput(const Uint8 * key){}

	virtual void Update(float delta){}
	
	virtual void OnUpdate(){}

	class Actor * Owner()const { return mOwner; }

	int UpdateOrder()const { return mUpdateOrder; }

private:
	class Actor *mOwner;
	int mUpdateOrder;

};

