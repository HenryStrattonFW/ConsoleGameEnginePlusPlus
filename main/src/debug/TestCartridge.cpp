//
// Created by Henry on 13/11/2022.
//

#include "../../include/debug/TestCartridge.h"
#include "../../include/core/Utils.h"
#include "../../include/core/Input.h"
#include <string>
#include <format>

namespace ConsoleGameEngine
{
	double lastDelta = 0;
	COORD nestedOffset{8, 40};// TODO: Source from actual console.
	
	void TestCartridge::OnInitialize()
	{
		nestedCanvas = new Canvas(64,24);
	}
	
	void TestCartridge::OnDeinitialize()
	{
		delete nestedCanvas;
	}
	
	
	std::string TestCartridge::CartridgeName()
	{
		return "Test Cartridge";
	}
	
	void TestCartridge::Update(double deltaTimeMs)
	{
		lastDelta = deltaTimeMs;
		
		COORD nSize = nestedCanvas->GetSize();
		nestedCanvas->Clear(BackgroundColour::Gray);
		
		COORD mPos = Input::MousePosition();
		mPos.X -= nestedOffset.X;
		mPos.Y -= nestedOffset.Y;
		nestedCanvas->DrawLine(0,mPos.Y, nSize.X, mPos.Y, ForegroundColour::Red);
		nestedCanvas->DrawLine(mPos.X, 0, mPos.X, nSize.Y, ForegroundColour::Red);
		
		nestedCanvas->DrawRect(0,0,nSize.X, nSize.Y, ForegroundColour::Blue);
	}
	
	void TestCartridge::Render(Canvas& canvas)
	{
		// Draw a simple frame.
		canvas.Clear(BackgroundColour::Maroon);
		canvas.FillRect(4,4,canvas.GetSize().X-8,canvas.GetSize().Y-8,ForegroundColour::Black);
		
		// Draw some labels.
		Utils::DrawTextCentered(canvas,8,"Running: TestCartridge", ForegroundColour::White);
		Utils::DrawTextCentered(canvas,12, std::format("Delta Time: {0}ms", lastDelta), ForegroundColour::White);
		Utils::DrawTextCentered(canvas,15,"Some Noise", ForegroundColour::White);
		
		//Render out some random noise.
		COORD noiseSize{32,18};
		COORD offset;
		offset.X = (canvas.GetSize().X /2)-(noiseSize.X /2);
		offset.Y = 17;
		for(short y=0;y<noiseSize.Y;y++)
			for(short x=0;x<noiseSize.X; x++)
				canvas.SetPixel(x+offset.X, y+offset.Y, rand()%256, Utils::RandomForeground(), Utils::RandomBackground());
				
		Utils::DrawTextCentered(canvas,nestedOffset.Y,"Nested Canvas", ForegroundColour::White);
		canvas.DrawCanvas(*nestedCanvas, nestedOffset.X, nestedOffset.Y+1);
	}
	
} // ConsoleGameEngine