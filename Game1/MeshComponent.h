#pragma once
#include "Component.h"
class MeshComponent :
	public Component
{
public:
	MeshComponent(class Actor * owner);
	~MeshComponent();

	void Draw(class Shader * shader);

	//Set/Get
	void SetMesh(class Mesh * mesh) { mMesh = mesh; }

	class Mesh * GetMesh()const { return mMesh; }

	//Tex index
	void SetTextureIndex(size_t index) { mTextureIndex = index; }

private:
	class Mesh * mMesh;
	size_t mTextureIndex;

};

