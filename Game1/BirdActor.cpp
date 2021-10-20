#include "BirdActor.h"

#include "MeshComponent.h"
#include "ParticleComponent.h"
#include "BoxComponent.h"

#include "Mesh.h"
#include "Renderer.h"
#include "Game.h"
#include "PhysicEngine.h"
#include "Random.h"
#include "GameOverMenu.h"


//This variable is when have been 3 Bird that has reached the floor this means the game is over
int BirdActor::mDeadCounter = 0;


BirdActor::BirdActor(Game * game)
	:Actor(game),
	mMaxTimeReachFloor(3)
{
	SetPosition(Vector3(350.0f, Random::FloatInRange(-200.0f, 200.0f), -100.0f));

	ParticleComponent *pc = new ParticleComponent(this);

	MeshComponent * m = new MeshComponent(this);

	m->SetMesh(game->GetRenderer()->GetMesh("Cube.gpmesh"));

	BoxComponent * box = new BoxComponent(this);

	box->SetObjectBox(m->GetMesh()->Box());


	//Scale this bird
	if (game->NumBirdKilled() >= 2 && game->NumBirdKilled() <= 4)
	{
		SetScale(0.2f);
	}
	else if (game->NumBirdKilled() > 4)
	{
		SetScale(0.1f);
	}
	else
	{
		//Start with this size
		SetScale(0.3f);
	}
	

	//Add bird in game
	game->AddBird(this);
}

BirdActor::~BirdActor()
{
	//Remove bird from game
	GetGame()->RemoveBird(this);
}

void BirdActor::UpdateActor(float dalta)
{
	//This check for Birds that have reached the floor
	if (Position().z <= -100)
	{
		mDeadCounter++;
		if (mDeadCounter == mMaxTimeReachFloor)
		{
			GameOverMenu * over = new GameOverMenu(GetGame());
			return;
		}

		//Create a new bird
		BirdActor * b = new BirdActor(GetGame());

		//Eliminate myself
		delete this;
	}
}
