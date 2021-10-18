#include "Bullet.h"

#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Collision.h"
#include "PhysicEngine.h"
#include "BirdActor.h"

#include "MeshComponent.h"
#include "MovementComponent.h"
#include "BoxComponent.h"


Bullet::Bullet(Game * game)
	:Actor(game)
{
	//The player components
	MeshComponent * mc = new MeshComponent(this);

	mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Sphere.gpmesh"));

	MovementComponent * move = new MovementComponent(this);

	//Veloyity
	move->SetForwardSpeed(60.0f);

}

void Bullet::UpdateActor(float delta)
{
	const float length = 30.0f;

	Vector3 start = Position();
	Vector3 end = start + Forward3() * length;

	LineSegment l = LineSegment(start, end);
	
	//Actor
	Actor * actor = nullptr;

	//If intersect then delete this bullet
	if (GetGame()->Physic()->SegmentCast(l, &actor))
	{
		BirdActor * bird = dynamic_cast<BirdActor *>(actor);

		//Delete this bird that was killed
		if (bird)
		{

			BirdActor *temp = new BirdActor(GetGame());

			delete bird;
			
		}


		delete this;
	}

	if (Position().x > 500.f)
	{
		
		delete this;
	}

}
