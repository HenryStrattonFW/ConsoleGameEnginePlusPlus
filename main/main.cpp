#include "include/core/GameConsole.h"
#include "include/debug/TestCartridge.h"

using namespace ConsoleGameEngine;

int main()
{
	TestCartridge* cart = new TestCartridge();
	GameConsole game("Test", 80, 72);
	game.Run(*cart);
	return 0;
}
