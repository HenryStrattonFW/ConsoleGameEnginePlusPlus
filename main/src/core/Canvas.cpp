//
// Created by Henry on 13/11/2022.
//

#include "../../include/core/Canvas.h"
#include "../../include/core/Colours.h"
#include <cassert>

using namespace std;

namespace ConsoleGameEngine
{
	Canvas::Canvas(short width, short height)
	{
		size = {width, height};
		buffer = new CHAR_INFO[width*height];
		Clear();
	}
	
	Canvas::~Canvas()
	{
		delete[] buffer;
	}
	
	
	CHAR_INFO* Canvas::GetBuffer()
	{
		return buffer;
	}
	
	COORD Canvas::GetSize()
	{
		return size;
	}
	
	
	void Canvas::Clear()
	{
		Clear(BackgroundColour::Black);
	}
	
	void Canvas::Clear(BackgroundColour colour)
	{
		for (int y = 0; y < size.Y; ++y)
		{
			for (int x = 0; x < size.X; ++x)
			{
				int idx = x + (size.X * y);
				buffer[idx].Char.AsciiChar = static_cast<char>(PixelType::None);
				buffer[idx].Attributes = static_cast<unsigned short>(colour);
			}
		}
	}
	
	
	void Canvas::SetPixel(short x, short y, char symbol, ForegroundColour colour, BackgroundColour bg)
	{
		if (x < 0 || y < 0 || x >= size.X || y >= size.Y)
			return;
		
		int idx = x + (size.X * y);
		buffer[idx].Char.AsciiChar = symbol;
		buffer[idx].Attributes = static_cast<unsigned short>(colour) | static_cast<unsigned short>(bg);
	}
	
	void Canvas::SetPixel(short x, short y, char symbol, ForegroundColour colour)
	{
		if (x < 0 || y < 0 || x >= size.X || y >= size.Y)
			return;
		
		int idx = x + (size.X * y);
		buffer[idx].Char.AsciiChar = symbol;
		buffer[idx].Attributes = static_cast<unsigned short>(colour);
	}
	
	
	void Canvas::DrawText(short x, short y, string text, ForegroundColour colour)
	{
		for(int i=0;i<text.length();i++)
			SetPixel(x+i, y, text[i], colour);
	}
	
	void Canvas::DrawCanvas(Canvas& otherCanvas, short x, short y)
	{
		for(short y2=0; y2 < otherCanvas.size.Y; y2++)
		{
			for(short x2=0; x2 < otherCanvas.size.X; x2++)
			{
				short tx = x+x2;
				short ty = y+y2;
				if (tx < 0 || ty < 0 || tx >= size.X || ty >= size.Y)
					continue;
				
				int idxOther = x2 + (otherCanvas.size.X * y2);
				int idx = tx + (size.X * ty);
				buffer[idx].Char.AsciiChar = otherCanvas.buffer[idxOther].Char.AsciiChar;
				buffer[idx].Attributes = otherCanvas.buffer[idxOther].Attributes;
			}
		}
	}
	
	
	void Canvas::DrawRect(short x, short y, short w, short h, ForegroundColour colour)
	{
		if (w <= 0 || h <= 0 || x >= size.X || (x + w) < 0 || y >= size.Y || (y + h) < 0)
			return;
		
		for (short ix = 0; ix < w; ix++)
		{
			SetPixel(x + ix, y, static_cast<char>(PixelType::Full), colour);
			SetPixel(x + ix, y + (h - 1), static_cast<char>(PixelType::Full), colour);
		}
		for (short iy = 0; iy < h; iy++)
		{
			SetPixel(x, y + iy, static_cast<char>(PixelType::Full), colour);
			SetPixel(x + (w - 1), y + iy, static_cast<char>(PixelType::Full), colour);
		}
	}
	
	void Canvas::FillRect(short x, short y, short w, short h, ForegroundColour colour)
	{
		if (w <= 0 || h <= 0 || x >= size.X || (x + w) < 0 || y >= size.Y || (y + h) < 0)
			return;
		
		for (short ix = 0; ix < w; ix++)
			for (short iy = 0; iy < h; iy++)
				SetPixel(x + ix, y + iy, static_cast<char>(PixelType::Full), colour);
	}
	
	void Canvas::FillRect(short x, short y, short w, short h, ForegroundColour strokeColour, ForegroundColour fillColour)
	{
		DrawRect(x, y, w, h, strokeColour);
		FillRect(x + 1, y + 1, w - 2, h - 2, fillColour);
	}
	
	
	void Canvas::DrawCircle(short x, short y, float radius, ForegroundColour colour)
	{
		if (x + radius < 0 || x - radius >= size.X || y + radius < 0 || y - radius >= size.Y)
			return;
		
		float d = (5 - radius * 4) / 4;
		float temp = 0;
		do
		{
			SetPixel(x + temp, y + radius, static_cast<char>(PixelType::Full), colour);
			SetPixel(x + temp, y - radius, static_cast<char>(PixelType::Full), colour);
			SetPixel(x - temp, y + radius, static_cast<char>(PixelType::Full), colour);
			SetPixel(x - temp, y - radius, static_cast<char>(PixelType::Full), colour);
			SetPixel(x + radius, y + temp, static_cast<char>(PixelType::Full), colour);
			SetPixel(x + radius, y - temp, static_cast<char>(PixelType::Full), colour);
			SetPixel(x - radius, y + temp, static_cast<char>(PixelType::Full), colour);
			SetPixel(x - radius, y - temp, static_cast<char>(PixelType::Full), colour);
			
			if (d < 0)
			{
				d += 2 * temp + 1;
			}
			else
			{
				d += 2 * (temp - radius) + 1;
				radius--;
			}
			temp++;
		} while (temp <= radius);
	}
	
	void Canvas::FillCircle(short x, short y, float radius, ForegroundColour colour)
	{
		if (x + radius < 0 || x - radius >= size.X || y + radius < 0 || y - radius >= size.Y)
			return;
		
		float d = (5 - radius * 4) / 4;
		float temp = 0;
		do
		{
			DrawLine(x + temp, y + radius, x + temp, y - radius, colour);
			DrawLine(x - temp, y + radius, x - temp, y - radius, colour);
			DrawLine(x + radius, y + temp, x + radius, y - temp, colour);
			DrawLine(x - radius, y + temp, x - radius, y - temp, colour);
			
			if (d < 0)
			{
				d += 2 * temp + 1;
			}
			else
			{
				d += 2 * (temp - radius) + 1;
				radius--;
			}
			temp++;
		} while (temp <= radius);
	}
	
	void Canvas::FillCircle(short x, short y, float radius, ForegroundColour strokeColour, ForegroundColour fillColour)
	{
		FillCircle(x, y, radius, fillColour);
		DrawCircle(x, y, radius, strokeColour);
	}
	
	
	void Canvas::DrawLine(short x1, short y1, short x2, short y2, ForegroundColour colour)
	{
		int dx = (int) abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
		int dy = (int) abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
		int err = (dx > dy ? dx : -dy) / 2, e2;
		
		while (x1 != x2 || y1 != y2)
		{
			SetPixel(x1, y1, static_cast<char>(PixelType::Full), colour);
			e2 = err;
			if (e2 > -dx)
			{
				err -= dy;
				x1 += sx;
			}
			if (e2 < dy)
			{
				err += dx;
				y1 += sy;
			}
		}
	}
}// ConsoleGameEngine