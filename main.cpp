#include "./include/ConsoleGame.h"
using namespace ConsoleGameEngine;

int main()
{
	ConsoleGame game("Test", 128, 72);
	
	while(game.IsGameActive())
	{
		game.ClearScreen();
		game.Update();
		game.Render();
		Sleep(100);
	}
	
	return 0;
}
