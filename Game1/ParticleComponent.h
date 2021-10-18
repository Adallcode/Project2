#pragma once
#include "Component.h"
#include "Math.h"


class ParticleComponent :
	public Component
{
public:
	ParticleComponent(class Actor * owner);

	void Update(float delta)override;


	//Add force
	void AddForce( Vector3& dir, float force);


	//Set/Get
	void SetVelocity(const Vector3& v) { mVelocity = v; }
	void SetForce(float f) { mforce = f; }
	void SetMass(float m) { mMass = m; }
	void SetGravity(float g) { mGravity = g; }


	Vector3 Velocity()const { return mVelocity; }
	float Force()const { return mforce; }
	float Mass()const { return mMass; }
	float Gravity()const { return mGravity; }

private:
	Vector3 mVelocity;
	float mforce;
	float mMass;
	float mGravity;

};

