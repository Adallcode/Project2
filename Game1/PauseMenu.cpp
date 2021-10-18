#include "PauseMenu.h"

#include "Game.h"

PauseMenu::PauseMenu(Game * game)
	:UIBase(game)
{
	game->SetState(Game::Pause);

	//Initialize the title 
	SetTitle("Pause");

	AddButton(
		[this]() { Closing(); }, "Resume");

	AddButton(
		[this]() { mGame->SetState(Game::Quit); }, "Quit");
}

PauseMenu::~PauseMenu()
{
	mGame->SetState(Game::GamePlay);
}

void PauseMenu::HandleKey(int key)
{
	UIBase::HandleKey(key);

	switch (key)
	{
	case SDLK_1:
		Closing();
		break;

	default:
		break;
	}
}
