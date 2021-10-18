#pragma once

#include "SDL.h"

#include <vector>
#include <unordered_map>
#include <string>
#include "Math.h"

struct DirectionalLight
{
	//Direction of light
	Vector3 mDirection;
	//Diffuse color
	Vector3 mDiffuseColor;
	//Specular color
	Vector3 mSpecColor;
};


class Renderer
{
public:
	Renderer(class Game * game, float windowW, float windowH);
	~Renderer();

	//Initialize
	bool Initialize();


	//Shutdown
	void Shutdown();

	//Draw1
	void Draw();
	

	//Create Shader
	bool CreateShader();

	//Create vertex
	void CreateVertex();


	//Set
	void SetWindowW(float windowW) { mWindowW = windowW; }
	void SetWindowH(float windowH) { mWindowH = windowH; }

	float WindowW()const { return mWindowW; }
	float WindowH()const { return mWindowH; }

	//Sprite and Mesh component
	void AddSprite(class SpriteComponent *sprite);
	void RemoveSprite(class SpriteComponent *sprite);


	void AddMeshComponent(class MeshComponent * mc);
	void RemoveMeshComponent(class MeshComponent * mc);

	//Textures
	class Texture *GetTexture(const std::string & fileName);

	//Mesh
	class Mesh *GetMesh(const std::string & fileName);

	//Game
	class Game * GetGame()const { return mGame; }

	//Ambient and Directional light
	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	DirectionalLight& GetDirectionalLight() { return mDirLight; }


	//View matrix
	void SetView(const Matrix4& view) { mView = view; }

private:
	//Helper for light
	void SetLightUniforms(class Shader* shader);

	//Lighting data
	Vector3 mAmbientLight;
	DirectionalLight mDirLight;

	// View/projection for 3D shaders
	Matrix4 mView;
	Matrix4 mProjection;

	float mWindowW;
	float mWindowH;

	//Window
	SDL_Window * mWindow;

	//Context
	SDL_GLContext mContext;

	//Shader
	class Shader * mMeshShader;
	class Shader * mShader;

	//Vertex Array
	class VertexArray * mVertexArray;

	//Sprite and Mesh component
	std::vector<class SpriteComponent *> mSprite;
	std::vector<class MeshComponent *> mMeshComponent;

	//Textures
	std::unordered_map<std::string, class Texture*> mTexture;

	//Meshes
	std::unordered_map<std::string, class Mesh*> mMesh;


	//Game
	class Game * mGame;
};

