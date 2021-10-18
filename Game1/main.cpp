#include <iostream>
#include "Game.h"
#include "Collision.h"
#include "Math.h"

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