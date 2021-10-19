#pragma once

#include <vector>
#include <stack>
#include <unordered_map>

#include "SDL.h"

class Game
{
public:
	Game();

	enum State{ GamePlay, Pause, Quit };

	bool Initialize();

	void Running();

	void Shutdown();

	//Actors
	void AddActor(class Actor * actor);
	void RemoveActor(class Actor * actor);

	//Bird actor
	void AddBird(class BirdActor * bird);
	void RemoveBird(class BirdActor * bird);


	//Load and Un load data
	void Load();
	void UnLoad();


	//Renderer
	class Renderer * GetRenderer()const { return mRenderer; }


	//Physic
	class PhysicEngine * Physic()const { return mPhysic; }

	//Font
	class Font * GetFont(const std::string& fileName);

	//State
	State GetState()const { return mState; }
	void SetState(const State& state) { mState = state; }


	//UI
	void AddUI(class UIBase * ui);

	const std::vector<class UIBase *> & UI()const { return mUI; }


	// Number of birds killed
	int NumBirdKilled()const { return mNumBirdKilled; }
	void IncreaseBirdKilled() { mNumBirdKilled++; }

private:
	bool mIsRunning;
	bool mUpdating;

	Uint32 mTicks;

	//Renderer
	class Renderer *mRenderer;

	//Physic
	class PhysicEngine * mPhysic;

	//Actors
	std::vector<class Actor *> mActor;
	std::vector<class Actor *> mPendingActor;


	//Birds
	std::vector<class BirdActor *> mBird;
	static int mNumBirdKilled;
	
	//Font
	std::unordered_map<std::string, class Font *> mFonts;

	//State
	State mState;

	//UI
	std::vector<class UIBase *> mUI;

	//Helpers
	void ProcessInput();
	void Update();
	void GenerateOutput();
	void HandleKey(int key);

};

