#include "PlaneActor.h"

#include "BoxComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Game.h"

PlaneActor::PlaneActor(Game * game)
	:Actor(game)
{
	//SetPosition(Vector3(300.f, 0.f, -100.f));
	SetScale(10.0f);
	MeshComponent * m = new MeshComponent(this);
	
	m->SetMesh(GetGame()->GetRenderer()->GetMesh("Plane.gpmesh"));

	mBox = new BoxComponent(this);

	mBox->SetObjectBox(m->GetMesh()->Box());

}
