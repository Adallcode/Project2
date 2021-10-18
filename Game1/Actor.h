#pragma once

#include <vector>

#include "Math.h"
#include "SDL.h"


class Actor
{
public:
	Actor(class Game *game);
	virtual ~Actor();

	enum State
	{
		Active, Dead
	};

	void ProcessInput(const Uint8 * key);
	void Update(float delta);
	void TransfromWorld();

	//Virtuals
	virtual void ActorInput(const Uint8 * key){}
	virtual void UpdateActor(float delta);


	//Get/Set
	void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorld = true; }
	void SetRotation(const float& rotation) { mRotation = rotation; mRecomputeWorld = true; }
	void SetQRotation(const Quaternion& q) { mQRotation = q; mRecomputeWorld = true; }
	void SetScale(const float& scale) { mScale = scale; mRecomputeWorld = true; }

	const Vector3& Position()const { return mPosition; }
	float Rotation()const { return mRotation; }
	Quaternion QRotation()const { return mQRotation; }
	float Scale()const { return mScale; }

	
	//Transformation
	void SetWorldTransform(Matrix4& transform) { mWorldTransform = transform; }
	Matrix4 WorldTransform()const { return mWorldTransform; }

	
	//Forward
	Vector3 Forward()const { return Vector3(Math::Cos(mRotation), Math::Sine(mRotation), 0.f); }

	Vector3 Forward3()const { return  Vector3::TransformByQuaternion(Vector3::UnitX, mQRotation); }

	Vector3 RightForward()const { return  Vector3::TransformByQuaternion(Vector3::UnitY, mQRotation); }


	//State
	void SetState(const State& state) { mState = state; }
	State GetState()const { return mState; }
	
	
	//Game
	class Game *GetGame()const { return mGame; }

	//Component
	void AddComponent(class Component * component);
	void RemoveComponent(class Component * component);

	void UpdateComponent(float delta);

private:
	bool mRecomputeWorld;
	Matrix4 mWorldTransform;


	Vector3 mPosition;
	float mScale;
	float mRotation;
	Quaternion mQRotation;

	State mState;

	//Components
	std::vector<class Component*> mComponent;
	

	class Game *mGame;
};

