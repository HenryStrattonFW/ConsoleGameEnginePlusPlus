#include "./include/ConsoleGame.h"
#include "./include/Input.h"

using namespace ConsoleGameEngine;

constexpr COORD screenSize = {64,36};

int main()
{
	ConsoleGame game("Test", screenSize.X, screenSize.Y);
	
	while (game.IsGameActive())
	{
		game.Update();
		
		Canvas &canvas = game.GetCanvas();
		COORD mPos = Input::MousePosition();
		ForegroundColour col = Input::MouseButtonDown(MouseButton::Left) ? ForegroundColour::Red : ForegroundColour::Blue;
		canvas.DrawLine(0,mPos.Y, screenSize.X, mPos.Y, col);
		canvas.DrawLine(mPos.X,0, mPos.X, screenSize.Y, col);
		
		game.Render();
		
		if(Input::WasKeyPressed(VK_ESCAPE))
			game.Quit();
		
		Sleep(10);
	}
	
	return 0;
}
