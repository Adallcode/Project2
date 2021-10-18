#include "Player.h"


#include "Bullet.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"

#include "MeshComponent.h"
#include "MovementComponent.h"




Player::Player(Game * game)
	:Actor(game),
	mShoot(false),
	mTimeToShoot(1.0f)
{
	MeshComponent * mc = new MeshComponent(this);

	mc->SetMesh(game->GetRenderer()->GetMesh("Rifle.gpmesh"));
	SetScale(0.3f);
}

void Player::ActorInput(const Uint8 * key)
{
	//Store the mouse position
	int x, y;

	SDL_GetMouseState(&x, &y);

	//Convert the mouse position into the screen coordinate

	mTarget.x = 400.0f;
	mTarget.y = ( x - GetGame()->GetRenderer()->WindowW() / 2.0f);
	mTarget.z = ( GetGame()->GetRenderer()->WindowW() / 2.0f - y );


	
	if (key[SDL_SCANCODE_L] && mTimeToShoot >= 1.0f)
	{
		mShoot = true;
		
	}
}

void Player::UpdateActor(float delta)
{
	//Find my Rifle direction
	Vector3 toTargetDir = Vector3::Normilize(mTarget - Position());

	//Axis of rotation
	Vector3 axis = Vector3::Cross(Forward3(), toTargetDir);
	axis.Normilize();

	float angle = Math::Acos(Vector3::Dot(Forward3(), toTargetDir));

	Quaternion rot = QRotation();

	angle = angle * delta;

	Quaternion q = Quaternion(axis, angle);

	q = Quaternion::Concatenate(rot, q);

	SetQRotation(q);

	//Make shot or not

	mTimeToShoot += delta;

	if (mShoot )
	{
		Shoot(q);

		//Put time back to 0
		mTimeToShoot = 0.0f;
	}

	
	
}

void Player::Shoot(const Quaternion& q)
{
	//Make this variable false 
	mShoot = false;

	Bullet * bullet = new Bullet(GetGame());

	//Set the properties of this player
	Vector3 pos = Position();
	pos += Forward3() * 20.0f;

	bullet->SetPosition(pos);
	bullet->SetScale(0.1f);
	bullet->SetQRotation(q);

	
}
