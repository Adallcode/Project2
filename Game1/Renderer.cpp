#include "Renderer.h"

#include "glew.h"
#include "Game.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Math.h"
#include "Mesh.h"
#include "UIBase.h"

#include "SpriteComponent.h"
#include "MeshComponent.h"

Renderer::Renderer(Game * game, float windowW, float windowH)
	:mGame(game),
	mWindowW(windowW),
	mWindowH(windowH),
	mWindow(nullptr),
	mMeshShader(nullptr),
	mShader(nullptr),
	mVertexArray(nullptr)
{
}

Renderer::~Renderer()
{
	//Call destructor from Game after shutdown

}

bool Renderer::Initialize()
{
	//Set attributes

	//Opengl core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	//Opengl version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	//Opengl color
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	//Depth
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//Double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	
	//Create window
	mWindow = SDL_CreateWindow("Game1", 100, 50, (int)mWindowW, (int)mWindowH, SDL_WINDOW_OPENGL);

	if (!mWindow)
	{
		SDL_Log("Window could not be initialized.");
		return false;
	}


	//Context
	mContext = SDL_GL_CreateContext(mWindow);


	//Initialize Glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Glew could not be initialized.");
		return false;
	}

	glGetError();


	if (!CreateShader())
	{
		SDL_Log("Shader could not be loaded.");
		return false;
	}

	CreateVertex();

	
	
	return true;
}


void Renderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Mesh
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	//here the mesh shader active
	mMeshShader->SetActive();

	//Update the view
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	//Set light
	SetLightUniforms(mMeshShader);

	//And draw
	for (auto m : mMeshComponent)
	{
		
		m->Draw(mMeshShader);
	}


	//Sprite
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	mShader->SetActive();
	mVertexArray->Active();
	
	
	//Renderer sprite
	for (auto s : mSprite)
	{
		s->Draw(mShader);
	}

	//Draw ui
	for (auto ui : mGame->UI())
	{
		ui->Draw(mShader);
	}

	SDL_GL_SwapWindow(mWindow);
}

bool Renderer::CreateShader()
{
	mShader = new Shader();

	if (!mShader->Load("Vertex.Basic", "Frag.Basic"))
	{
		return false;
	}

	mShader->SetActive();

	Matrix4 view = Matrix4::View(mWindowW, mWindowH);

	mShader->SetMatrixUniform("mView", view);

	//Mesh shader
	mMeshShader = new Shader();

	if (!mMeshShader->Load("Phong.vert", "Phong.frag"))
	{
		return false;
	}

	mMeshShader->SetActive();

	mView = Matrix4::Lookat(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadian(70.f), mWindowW, mWindowH, 25.0f, 10000.0f);

	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	return true;
}

void Renderer::CreateVertex()
{
	float vertex[] =
	{
		//Position, normal
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
		0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f,
		-0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f
	};


	unsigned int index[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	mVertexArray = new VertexArray(vertex, 4, index, 6);
	
}

//Sprite and Mesh component
void Renderer::AddSprite(SpriteComponent *sprite)
{
	mSprite.push_back(sprite);
	
}

void Renderer::RemoveSprite(SpriteComponent *sprite)
{
	
	auto  it = std::find(mSprite.begin(), mSprite.end(), sprite);

	if (it != mSprite.end())
	{
		mSprite.erase(it);
	}
	
}


void Renderer::AddMeshComponent(class MeshComponent * mc)
{
	mMeshComponent.push_back(mc);
}

void Renderer::RemoveMeshComponent(class MeshComponent * mc)
{
	auto it = std::find(mMeshComponent.begin(), mMeshComponent.end(), mc);

	if (it != mMeshComponent.end())
	{
		mMeshComponent.erase(it);
	}
}

//Get texture and mesh
Texture * Renderer::GetTexture(const std::string & fileName)
{
	Texture *temp = nullptr;

	auto it = mTexture.find(fileName);

	if (it != mTexture.end())
	{
		return it->second;
	}
	else
	{
		//Not found in the map
		temp = new Texture();

		if (!temp->Load(fileName.c_str()))
		{
			delete temp;
			temp = nullptr;

			return temp;
		}

		//It has loaded the texture
		mTexture.emplace(fileName, temp);

		return temp;
	}
}

Mesh * Renderer::GetMesh(const std::string & fileName)
{
	Mesh *temp = nullptr;

	auto it = mMesh.find(fileName);

	if (it != mMesh.end())
	{
		return it->second;
	}
	else
	{
		//Not found in the map
		temp = new Mesh();

		if (!temp->Load(fileName.c_str(), this))
		{
			delete temp;
			temp = nullptr;

			return temp;
		}

		//It has loaded the texture
		mMesh.emplace(fileName, temp);

		return temp;
	}
}


//Helper for light
void Renderer::SetLightUniforms(class Shader* shader)
{
	// Camera position is from inverted view
	Matrix4 invView = mView;
	invView.Invert();
	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// Ambient light
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// Directional light
	shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.mDirection);
	shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.mDiffuseColor);
	shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.mSpecColor);
}

void Renderer::Shutdown()
{
	//Components
	mSprite.clear();
	mMeshComponent.clear();


	//Textures
	for (auto t : mTexture)
	{
		delete t.second;
	}
	mTexture.clear();


	//Mesh
	for (auto m : mMesh)
	{
		delete m.second;
	}
	mMesh.clear();

	delete mVertexArray;
	delete mMeshShader;
	delete mShader;

	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);

}
