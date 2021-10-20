#include "Game.h"

#include "SDL.h"
#include <algorithm>

#include "Renderer.h"
#include "Actor.h"
#include "Texture.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Math.h"
#include "Random.h"
#include "SDL_ttf.h"
#include "Font.h"
#include "UIBase.h"
#include "PauseMenu.h"

#include "CamaraComponent.h"
#include "PhysicEngine.h"

#include "PlaneActor.h"
#include "Player.h"
#include "BirdActor.h"


//Number of birds killed
int Game::mNumBirdKilled = 0;

const float W = 1000.f;
const float H = 700.f;


Game::Game()
	:mIsRunning(true),
	mUpdating(false),
	mTicks(0),
	mState(GamePlay)
{
	//Reserve space
	mActor.reserve(2000);
}

bool Game::Initialize()
{
	int initOpengl = SDL_Init(SDL_INIT_VIDEO);
	
	if (initOpengl != 0)
	{
		SDL_Log("Could not initialize SDL.");
		return false;
	}


	if (TTF_Init() != 0)
	{
		SDL_Log("Could not initialize TTF.");
		return false;
	}

	mRenderer = new Renderer(this, W, H);

	if (!mRenderer->Initialize())
	{
		return false;
	}

	//Initialize the random
	Random::Init();

	mPhysic = new PhysicEngine();

	Load();

	mTicks = SDL_GetTicks();

	return true;
}

//Load
void Game::Load()
{
	Player *p = new Player(this);

	p->SetPosition(Vector3(10.0f, 0.f, 0.0f));

	//Bird
	BirdActor * b = new BirdActor(this);

	//Camara
	Actor * a = new Actor(this);
	
	CamaraComponent * c = new CamaraComponent(a);


	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			a = new PlaneActor(this);
			a->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	Quaternion q = Quaternion(Vector3::UnitX, Math::PiOver2);
	for (int i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start + i * size, start - size, 0.0f));
		a->SetQRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(start + i * size, -start + size, 0.0f));
		a->SetQRotation(q);
	}

	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start - size, start + i * size, 0.0f));
		a->SetQRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(-start + size, start + i * size, 0.0f));
		a->SetQRotation(q);
	}


	
	
	

	// Setup lights
	mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
}


void Game::Running()
{
	while (mState != Quit)
	{
		//Call the helper funtions
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	UnLoad();

	//Shut down the library
	TTF_Quit();

	delete mPhysic;

	if (mRenderer)
	{
		mRenderer->Shutdown();
		delete mRenderer;
	}


	//Shut down SDL
	SDL_Quit();
}


void Game::ProcessInput()
{
	SDL_Event mEvent;

	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
		case SDL_QUIT:
			mState = Quit;
			break;

		case SDL_KEYDOWN:
			if (!mEvent.key.repeat)
			{
				if (mState == GamePlay)
				{
					HandleKey(mEvent.key.keysym.sym);
				}
				else if (!mUI.empty())
				{
					mUI.back()->HandleKey(mEvent.key.keysym.sym);
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (!mUI.empty())
			{
				mUI.back()->HandleKey(mEvent.button.button);
			}
			break;

		default:
			break;
		}
		

	}

	const Uint8 * key = SDL_GetKeyboardState(nullptr);
	
	if (key[SDL_SCANCODE_ESCAPE])
	{
		mState = Quit;
	}
	
	

	if (mState == GamePlay)
	{
		for (auto a : mActor)
		{
			a->ProcessInput(key);
		}
	}
	else if (!mUI.empty())
	{
		mUI.back()->ProcessInput(key);
	}
}


void Game::HandleKey(int key)
{
	switch (key)
	{
	case SDLK_1:
		
		//Create pause
		new PauseMenu(this);

		break;
	}
}


void Game::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicks + 16))
		;

	float delta = (SDL_GetTicks() - mTicks) / 1000.0f;

	//Just get this frame ticks
	mTicks = SDL_GetTicks();

	if (mState == GamePlay)
	{
		mUpdating = true;
		for (auto a : mActor)
		{
			a->Update(delta);
		}

		//Pass pending to actor, but before Transform it
		for (auto p : mPendingActor)
		{
			p->TransfromWorld();
			mActor.push_back(p);
		}
		mPendingActor.clear();

		//Dead actors
		std::vector<Actor *> dead;

		for (auto a : mActor)
		{
			if (a->GetState() == Actor::Dead)
			{
				dead.push_back(a);
			}
		}

		for (auto d : dead)
		{
			delete d;
		}

		mUpdating = false;
	}

	//Ui
	for (auto ui : mUI)
	{
		if (ui->GetState() == UIBase::EActive)
		{
			ui->Update(delta);
		}
	}

	//Delete and eleminate
	auto it = mUI.begin();
	while (it != mUI.end())
	{
		if ((*it)->GetState() == UIBase::EClosing)
		{
			delete *it;
			it = mUI.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}


//Actors
void Game::AddActor(Actor * actor)
{
	if (mUpdating)
	{
		mPendingActor.push_back(actor);
	}
	else
	{
		mActor.push_back(actor);
	}
}

void Game::RemoveActor(Actor * actor)
{
	auto it = std::find(mActor.begin(), mActor.end(), actor);

	if (it != mActor.end())
	{
		std::iter_swap(it, mActor.end() - 1);
		mActor.pop_back();
	}

	it = std::find(mPendingActor.begin(), mPendingActor.end(), actor);
	if (it != mPendingActor.end())
	{
		std::iter_swap(it, mPendingActor.end() - 1);
		mPendingActor.pop_back();
	}

	
}

//Birds
void Game::AddBird(BirdActor * bird)
{
	mBird.push_back(bird);
}

void Game::RemoveBird(BirdActor * bird)
{
	auto it = std::find(mBird.begin(), mBird.end(), bird);

	if (it != mBird.end())
	{
		mBird.erase(it);
	}
}


//Un load data
void Game::UnLoad()
{
	//Actors
	while (!mActor.empty())
	{
		delete mActor.back();
	}
	mActor.clear();

	while (!mPendingActor.empty())
	{
		delete mPendingActor.back();
	}
	mPendingActor.clear();

	
	//UI
	while (!mUI.empty())
	{
		delete mUI.back();
		mUI.pop_back();
	}
	

}

//UI
void Game::AddUI(class UIBase * ui)
{
	mUI.push_back(ui);
}


Font * Game::GetFont(const std::string & fileName)
{
	Font * font = nullptr;

	auto it = mFonts.find(fileName);

	if (it != mFonts.end())
	{
		font = it->second;

		return font;
	}
	else
	{
		font = new Font();

		if (!font->Load(fileName.c_str()))
		{
			delete font;
			font = nullptr;
		}
		else
		{
			mFonts.emplace(fileName, font);
		}
	}

	return font;
}
