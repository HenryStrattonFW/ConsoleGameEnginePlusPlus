//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_INPUT_H
#define CONSOLEGAMEENGINEPLUSPLUS_INPUT_H

using namespace std;

namespace ConsoleGameEngine
{
	enum class MouseButton
	{
		Left = FROM_LEFT_1ST_BUTTON_PRESSED,
		Right = RIGHTMOST_BUTTON_PRESSED,
		Middle = FROM_LEFT_2ND_BUTTON_PRESSED
	};
	
	namespace Input
	{
		void Update(HANDLE readHandle);
		bool IsKeyDown(unsigned short key);
		bool WasKeyPressed(unsigned short key);
		bool WasKeyReleased(unsigned short key);
		bool MouseButtonDown(MouseButton button);
		bool MouseButtonPressed(MouseButton button);
		bool MouseButtonReleased(MouseButton button);
		COORD MousePosition();
	};
	
} // ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_INPUT_H
