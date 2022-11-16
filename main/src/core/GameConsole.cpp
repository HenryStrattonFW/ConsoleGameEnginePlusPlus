//
// Created by Henry on 13/11/2022.
//

#include "../../include/core/GameConsole.h"
#include "../../include/core/Input.h"
#include "../../include/debug/Debug.h"
#include <chrono>

namespace ConsoleGameEngine
{
	GameConsole::GameConsole(string name, short width, short height)
	{
		Debug::Log("Creating GameConsole...");
		// Set up some stuff we want to keep track of.
		screenRect = {0,0,
					  static_cast<SHORT>(width-1),
					  static_cast<SHORT>(height-1)
		};
		screenSize = {width,height};
		activeCanvas = new Canvas(width, height);
		presentedCanvas = new Canvas(width, height);
		
		// Set up the handles for reading/writing:
		writeHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		readHandle = GetStdHandle(STD_INPUT_HANDLE);
		
		// Hide the cursor so that it doesn't interfere with other drawing.
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(writeHandle, &cursorInfo);
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(writeHandle, &cursorInfo);
		
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
		
		
		/*
		Note: Setting up font as last step as it seems to be the only way to avoid the console
		Getting extra space on each side, I would have thought setting size would take font into
		account but clearly something else is happening behind the scenes.
		*/
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize = {8,8};
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		std::wcscpy(cfi.FaceName, L"Terminal");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
		
		
		Debug::Log("GameConsole is ready!");
	}
	
	GameConsole::~GameConsole()
	{
		// TODO: Likely need some cleanup eventually here.
	}
	
	
	void GameConsole::Run(GameCartridge &cartridge)
	{
		SetConsoleTitle(cartridge.CartridgeName().c_str());
		Debug::Log(std::format("Booting Cartridge: {0}", cartridge.CartridgeName()));
		std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime,currentFrameTime;
		
		cartridge.Inititialize();
		while(cartridge.IsRunning())
		{
			lastFrameTime = currentFrameTime;
			currentFrameTime = std::chrono::high_resolution_clock::now();
			
			Update();
			double deltaMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime-lastFrameTime).count();
			cartridge.Update(deltaMs);
			cartridge.Render(*activeCanvas);
			
			Render();
			Sleep(10);
		}
		Debug::Log("Ejecting Cartridge.");
		cartridge.Deinitialize();
		Debug::Log("Run Complete.");
	}
	
	
	void GameConsole::Update()
	{
		activeCanvas->Clear(BackgroundColour::Black);
		Input::Update(readHandle);
	}
	
	void GameConsole::Render()
	{
		WriteConsoleOutputA(writeHandle,
							activeCanvas->GetBuffer(),
							activeCanvas->GetSize(),
							{0,0},
							&screenRect);
		
		std::swap(presentedCanvas, activeCanvas);
	}
	
} // ConsoleGameEngine