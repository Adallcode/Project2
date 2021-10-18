#include "GameOverMenu.h"
#include "Game.h"
#include "Renderer.h"

GameOverMenu::GameOverMenu(Game * game)
	:UIBase(game),
	mLifeTime(0.0f),
	mDeathTime(5.0f)
{
	game->SetState(Game::Pause);

	SetTitle("Game over", Color::Blue, 40);
	
	SetBackground(game->GetRenderer()->GetTexture("Assets/Farback01.png"));

	SetPosition(Vector3(0.f, 100.0f, 0.f));
}

GameOverMenu::~GameOverMenu()
{
	mGame->SetState(Game::Quit);
}

void GameOverMenu::Update(float delta)
{
	mLifeTime += delta;

	if (mLifeTime >= mDeathTime)
	{
		Closing();
	}
}
