#include "./include/ConsoleGame.h"
#include "./include/Input.h"
using namespace ConsoleGameEngine;

int main()
{
	ConsoleGame game("Test", 64, 36);
	
	while (game.IsGameActive())
	{
		game.ClearScreen();
		game.Update();
		
		if(Input::MouseButtonDown(MouseButton::Left))
		//if(Input::IsKeyDown(VK_SPACE))
		{
			Canvas &canvas = game.GetCanvas();
			for (short y = 0; y < canvas.GetSize().Y; y++)
			{
				for (short x = 0; x < canvas.GetSize().X; x++)
				{
					canvas.SetPixel(x,y,rand()%256, ForegroundColour::Green);
				}
			}
		}
		
		game.Render();
		Sleep(100);
	}
	
	return 0;
}
