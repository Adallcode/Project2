#include "Actor.h"

#include "Game.h"
#include "Texture.h"
#include "Component.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Mesh.h"

Actor::Actor(Game * game)
	:mGame(game),
	mPosition(Vector3::Zero),
	mRotation(0.f),
	mQRotation(Quaternion::Identity),
	mScale(1.0f),
	mRecomputeWorld(true),
	mState(Active)
{
	//Reserve space
	mComponent.reserve(1000);

	mGame->AddActor(this);
	
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	//Delete each component attach to this actor

	while (!mComponent.empty())
	{
		delete mComponent.back();
	}

	
}

void Actor::ProcessInput(const Uint8 * key)
{
	for (auto c : mComponent)
	{
		c->ProcessInput(key);
	}
	
	ActorInput(key);
}

void Actor::Update(float delta)
{
	if (mState == Active)
	{
		TransfromWorld();

		//Update component
		UpdateComponent(delta);

		//Update actor
		UpdateActor(delta);

		TransfromWorld();
	}
}

void Actor::UpdateActor(float delta)
{
	
}


void Actor::TransfromWorld()
{
	if (mRecomputeWorld)
	{
		mRecomputeWorld = false;

		mWorldTransform = Matrix4::Scale(mScale);
		//mWorldTransform *= Matrix4::Rotation(mRotation);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mQRotation);
		mWorldTransform *= Matrix4::Translate(mPosition);

		//For emergency case
		for (auto c : mComponent)
		{
			c->OnUpdate();
		}
	}
}


//Component
void Actor::UpdateComponent(float delta)
{
	for (auto c : mComponent)
	{
		c->Update(delta);
	}
}


void Actor::AddComponent(Component * component)
{
	int order = component->UpdateOrder();

	auto it = mComponent.begin();

	for (; it != mComponent.end(); ++it)
	{
		if ((*it)->UpdateOrder() > order)
		{
			break;
		}
	}
	//Emplece this component one position before
	mComponent.emplace(it, component);
}

void Actor::RemoveComponent(Component * component)
{
	auto it = std::find(mComponent.begin(), mComponent.end(), component);
	
	if (it != mComponent.end())
	{
		
		mComponent.erase(it);
	}
}