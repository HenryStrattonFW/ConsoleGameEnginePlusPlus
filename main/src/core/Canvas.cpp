//
// Created by Henry on 13/11/2022.
//

#include "../../include/core/Canvas.h"
#include "../../include/core/Utils.h"

#define CHAR(x) static_cast<char>(x)
#define USHORT(x) static_cast<unsigned short>(x)

using namespace std;

namespace ConsoleGameEngine
{
	Canvas::Canvas(short width, short height)
	{
		size = {width, height};
		buffer = new CHAR_INFO[width*height];
		canvasRect = {0,0,width,height};
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
				buffer[idx].Char.AsciiChar = CHAR(PixelType::None);
				buffer[idx].Attributes = USHORT(colour);
			}
		}
	}
	
	
	void Canvas::SetPixel(short x, short y, char symbol, ForegroundColour colour, BackgroundColour bg)
	{
		if (x < 0 || y < 0 || x >= size.X || y >= size.Y)
			return;
		
		int idx = x + (size.X * y);
		buffer[idx].Char.AsciiChar = symbol;
		buffer[idx].Attributes = USHORT(colour) | USHORT(bg);
	}
	
	void Canvas::SetPixel(short x, short y, char symbol, ForegroundColour colour)
	{
		if (x < 0 || y < 0 || x >= size.X || y >= size.Y)
			return;
		
		int idx = x + (size.X * y);
		buffer[idx].Char.AsciiChar = symbol;
		buffer[idx].Attributes = USHORT(colour);
	}
	
	
	void Canvas::DrawText(short x, short y, string text, ForegroundColour colour)
	{
		for(int i=0;i<text.length();i++)
			SetPixel(x+i, y, text[i], colour);
	}
	
	void Canvas::DrawCanvas(Canvas& otherCanvas, short x, short y)
	{
		SMALL_RECT overlap = Utils::GetOverlap(
				canvasRect,
				Utils::RectFromPosAndSize({x,y}, otherCanvas.size)
		);
		
		// No overlap.
		if(overlap.Right == 0 || overlap.Bottom == 0) return;
		
		short sourceLeft = x > 0 ? 0 : -x;
		short sourceTop = y > 0 ? 0 : -y;
		short width = (overlap.Right - overlap.Left);
		short height = (overlap.Bottom - overlap.Top);
		
		// Calculate the area of the incoming canvas that we can actually draw.
		for(short iy=0; iy < height; iy++)
		{
			for(short ix=0; ix < width; ix++)
			{
				int destIndex = (overlap.Left + ix) + (size.X * (overlap.Top + iy));
				int sourceIndex = (sourceLeft+ix) + (otherCanvas.size.X * (sourceTop+iy));
				buffer[destIndex].Char.AsciiChar = otherCanvas.buffer[sourceIndex].Char.AsciiChar;
				buffer[destIndex].Attributes = otherCanvas.buffer[sourceIndex].Attributes;
			}
		}
	}
	
	
	void Canvas::DrawRect(short x, short y, short w, short h, ForegroundColour colour)
	{
		if (w <= 0 || h <= 0 || x >= size.X || (x + w) < 0 || y >= size.Y || (y + h) < 0)
			return;
		
		for (short ix = 0; ix < w; ix++)
		{
			if(x+ix < 0) continue;
			SetPixel(x + ix, y, CHAR(PixelType::Full), colour);
			SetPixel(x + ix, y + (h - 1), CHAR(PixelType::Full), colour);
		}
		for (short iy = 0; iy < h; iy++)
		{
			if(y+iy < 0) continue;
			SetPixel(x, y + iy, CHAR(PixelType::Full), colour);
			SetPixel(x + (w - 1), y + iy, CHAR(PixelType::Full), colour);
		}
	}
	
	void Canvas::FillRect(short x, short y, short w, short h, ForegroundColour colour)
	{
		if (w <= 0 || h <= 0 || x >= size.X || (x + w) < 0 || y >= size.Y || (y + h) < 0)
			return;
		
		for (short ix = 0; ix < w; ix++)
		{
			if(x+ix < 0) continue;
			for (short iy = 0; iy < h; iy++)
			{
				if(y+iy < 0) continue;
				SetPixel(x + ix, y + iy, CHAR(PixelType::Full), colour);
			}
		}
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
			SetPixel(x + temp, y + radius, CHAR(PixelType::Full), colour);
			SetPixel(x + temp, y - radius, CHAR(PixelType::Full), colour);
			SetPixel(x - temp, y + radius, CHAR(PixelType::Full), colour);
			SetPixel(x - temp, y - radius, CHAR(PixelType::Full), colour);
			SetPixel(x + radius, y + temp, CHAR(PixelType::Full), colour);
			SetPixel(x + radius, y - temp, CHAR(PixelType::Full), colour);
			SetPixel(x - radius, y + temp, CHAR(PixelType::Full), colour);
			SetPixel(x - radius, y - temp, CHAR(PixelType::Full), colour);
			
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
		if((x1 < 0 && x2<0) || (x1>size.X && x2>size.X)) return;
		if((y1 < 0 && y2<0) || (y1>size.Y && y2>size.Y)) return;
		
		int dx = (int) abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
		int dy = (int) abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
		int err = (dx > dy ? dx : -dy) / 2, e2;
		
		while (x1 != x2 || y1 != y2)
		{
			SetPixel(x1, y1, CHAR(PixelType::Full), colour);
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