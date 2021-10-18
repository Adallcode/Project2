#include "CamaraComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

CamaraComponent::CamaraComponent(Actor * owner)
	:MovementComponent(owner)
{
}

void CamaraComponent::ProcessInput(const Uint8 * key)
{
	float forward = 0.0f;
	float angular = 0.0f;
	float right = 0.0f;

	if (key[SDL_SCANCODE_W])
	{
		forward += 100.0f;
	}

	if (key[SDL_SCANCODE_S])
	{
		forward -= 100.0f;
	}

	//Right
	if (key[SDL_SCANCODE_C])
	{
		right += 100.0f;
	}

	if (key[SDL_SCANCODE_X])
	{
		right -= 100.0f;
	}


	//Angular
	if (key[SDL_SCANCODE_D])
	{
		angular += Math::PiOver2;
	}

	if (key[SDL_SCANCODE_A])
	{
		angular -= Math::PiOver2;
	}

	SetAngularSpeed(angular);
	SetForwardSpeed(forward);
	SetmRightSpeed(right);
}

void CamaraComponent::Update(float delta)
{
	MovementComponent::Update(delta);

	//Eye
	Vector3 eye = Owner()->Position();

	Vector3 target = eye + Owner()->Forward3() * 100.0f;

	Matrix4 view = Matrix4::Lookat(eye, target, Vector3::UnitZ);

	Owner()->GetGame()->GetRenderer()->SetView(view);
}
