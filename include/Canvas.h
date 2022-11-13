//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_CANVAS_H
#define CONSOLEGAMEENGINEPLUSPLUS_CANVAS_H

#include <Windows.h>
#include "Colours.h"
#include <vector>

namespace ConsoleGameEngine
{
	class Canvas
	{
	public:
		Canvas(short width = 1, short height = 1);
		~Canvas();
		
		CHAR_INFO* GetBuffer();
		COORD GetSize();
		
		void Clear();
		void Clear(BackgroundColour colour);
		
		void SetPixel(short x, short y, char symbol, ForegroundColour colour, BackgroundColour bg);
		void SetPixel(short x, short y, char symbol, ForegroundColour colour);
		
		void DrawRect(short x, short y, short w, short h, ForegroundColour colour);
		void FillRect(short x, short y, short w, short h, ForegroundColour colour);
		void FillRect(short x, short y, short w, short h, ForegroundColour strokeColour, ForegroundColour fillColour);
		
		void DrawCircle(short x, short y, float radius, ForegroundColour colour);
		void FillCircle(short x, short y, float radius, ForegroundColour colour);
		void FillCircle(short x, short y, float radius, ForegroundColour strokeColour, ForegroundColour fillColour);
		
		void DrawLine(short x1, short y1, short x2, short y2, ForegroundColour colour);
	
	private:
		COORD size;
		CHAR_INFO* buffer;
	};
	
} // ConsoleGameEngine

#endif //CONSOLEGAMEENGINEPLUSPLUS_CANVAS_H
