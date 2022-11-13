//
// Created by Henry on 13/11/2022.
//

#include "../include/TestCartridge.h"

namespace ConsoleGameEngine
{
	void TestCartridge::Inititialize()
	{
	}
	
	void TestCartridge::Deinitialize()
	{
	
	}
	
	void TestCartridge::Update(double deltaTime)
	{
	
	}
	
	void TestCartridge::Render(Canvas& canvas)
	{
		canvas.DrawRect(5,5,16,16,ForegroundColour::Red);
	}
	
} // ConsoleGameEngine