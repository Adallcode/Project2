#include "ParticleComponent.h"

#include "Actor.h"
#include "Random.h"


ParticleComponent::ParticleComponent(Actor * owner)
	:Component(owner),
	mforce( Random::FloatInRange( 15.0f, 30.0f)),
	mMass(1.0f),
	mGravity( -Random::FloatInRange( 0.5f, 1.5f))
{
	Vector3 target = Vector3(400.f, Random::FloatInRange(-50.0f, 50.0f), Random::FloatInRange(10.0f, 50.0f));

	Vector3 toTarget = target - owner->Position();

	AddForce(toTarget, mforce);
}

void ParticleComponent::Update(float delta)
{
	Vector3 pos = Owner()->Position();

	mVelocity.z += delta * mGravity;

	pos += mVelocity  * delta;

	Owner()->SetPosition(pos);
}

void ParticleComponent::AddForce( Vector3 & dir, float force)
{
	dir.Normilize();

	mVelocity = (dir * force) / mMass;
}
