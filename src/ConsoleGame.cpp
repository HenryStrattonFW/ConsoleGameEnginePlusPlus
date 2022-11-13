//
// Created by Henry on 13/11/2022.
//

#include "../include/ConsoleGame.h"
#include "../include/Input.h"

namespace ConsoleGameEngine
{
	ConsoleGame::ConsoleGame(string name, short width, short height)
	{
		// Set up some stuff we want to keep track of.
		screenRect = {0,0,
					  static_cast<SHORT>(width-1),
					  static_cast<SHORT>(height-1)
		};
		screenSize = {width, height};
		screenCanvas = Canvas(width, height);
		gameActive = true;
		
		// Set up the handles for reading/writing:
		writeHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		readHandle = GetStdHandle(STD_INPUT_HANDLE);
		
		// Hide the cursor so that it doesn't interfere with other drawing.
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(writeHandle, &cursorInfo);
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(writeHandle, &cursorInfo);
		
		// Set us up on a square sized font for more sensible visuals.
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize = {8,8};
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		std::wcscpy(cfi.FaceName, L"Terminal"); // Choose your font
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
		
		// Set up the window.
		DWORD mode = 0;
		if(GetConsoleMode(readHandle, &mode))
		{
			mode |= ENABLE_MOUSE_INPUT;
			mode &= ~ENABLE_QUICK_EDIT_MODE;
			mode |= ENABLE_EXTENDED_FLAGS;
			SetConsoleMode(readHandle, mode);
		}
		SetConsoleTitle(name.c_str());
		SetConsoleWindowInfo(writeHandle, TRUE, &screenRect);
		SetConsoleScreenBufferSize(writeHandle, screenSize);
		
		// Disable resizing the window (just simpler than dealing with resizable stuff for now).
		HMENU sysMenu = GetSystemMenu(GetConsoleWindow(), false);
		DeleteMenu(sysMenu, SC_SIZE, MF_BYCOMMAND);
		DeleteMenu(sysMenu, SC_MINIMIZE, MF_BYCOMMAND);
		DeleteMenu(sysMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
	
	ConsoleGame::~ConsoleGame()
	{
		// TODO: Likely need some cleanup eventually here.
	}
	
	Canvas& ConsoleGame::GetCanvas()
	{
		return screenCanvas;
	}
	
	bool ConsoleGame::IsGameActive()
	{
		return gameActive;
	}
	
	void ConsoleGame::Update()
	{
		Input::Update(readHandle);
	}
	
	void ConsoleGame::ClearScreen()
	{
		screenCanvas.Clear();
	}
	
	void ConsoleGame::Render()
	{
		WriteConsoleOutputA(writeHandle,
							screenCanvas.GetBuffer(),
							screenSize,
							{0,0},
							&screenRect);
	}
	
} // ConsoleGameEngine