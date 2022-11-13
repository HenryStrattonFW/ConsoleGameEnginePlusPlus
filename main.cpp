#include "./include/GameConsole.h"
#include "./include/TestCartridge.h"

using namespace ConsoleGameEngine;

int main()
{
	GameCartridge* cart = new TestCartridge();
	GameConsole game("Test", 80, 72);
	game.Run(*cart);
	return 0;
}
