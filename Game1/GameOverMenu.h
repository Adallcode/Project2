#pragma once
#include "UIBase.h"
class GameOverMenu :
	public UIBase
{
public:
	GameOverMenu(class Game *game);
	~GameOverMenu();

	void Update(float delta)override;

private:
	float mLifeTime;
	float mDeathTime;
};

