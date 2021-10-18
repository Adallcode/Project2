#include "MeshComponent.h"

#include "glew.h"
#include "Mesh.h"
#include "Texture.h"
#include "Math.h"
#include "Actor.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Game.h"
#include "Renderer.h"

MeshComponent::MeshComponent(Actor * owner)
	:Component(owner),
	mMesh(nullptr),
	mTextureIndex(0)
{
	owner->GetGame()->GetRenderer()->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	Owner()->GetGame()->GetRenderer()->RemoveMeshComponent(this);
}

void MeshComponent::Draw(Shader * shader)
{
	if (mMesh)
	{
		//Send the owner matrix
		Matrix4 temp = Owner()->WorldTransform();
		shader->SetMatrixUniform("uWorldTransform", temp);

		//Send the specular power
		float specularPower = mMesh->GetSpecPower();
		shader->SetFloatUniform("uSpecPower", specularPower);

		//Active texture
		Texture * t = mMesh->GetTexture(mTextureIndex);
		if (t) { t->Active(); }
		
		//Active vertex array
		VertexArray * v = mMesh->GetVertexArray();
		v->Active();
		
		glDrawElements(GL_TRIANGLES, v->NumOfIndices(), GL_UNSIGNED_INT, nullptr);


	}
}
