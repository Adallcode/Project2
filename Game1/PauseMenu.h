#pragma once
#include "UIBase.h"
class PauseMenu :
	public UIBase
{
public:
	PauseMenu(class Game *game);
	~PauseMenu();

	void HandleKey(int key)override;
};

