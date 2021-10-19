#include <iostream>

#include "Game.h"


using namespace std;




int main(int argc, char** argv)
{
	
	Game game;
	
	bool s = game.Initialize();

	if (s)
	{
		
		game.Running();
	}
	game.Shutdown();

	return 0;
}