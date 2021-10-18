#pragma once
#include "MovementComponent.h"
class CamaraComponent :
	public MovementComponent
{
public:
	CamaraComponent(class Actor * owner);

	void ProcessInput(const Uint8 * key)override;
	void Update(float delta)override;

private:


};

