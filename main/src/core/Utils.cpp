//
// Created by Henry on 13/11/2022.
//

#include "../../include/core/Utils.h"

namespace ConsoleGameEngine
{
	namespace Utils
	{
		ForegroundColour RandomForeground()
		{
			const static ForegroundColour foregroundColours[] = {
					ForegroundColour::Black,
					ForegroundColour::Blue,
					ForegroundColour::Green,
					ForegroundColour::Cyan,
					ForegroundColour::Red,
					ForegroundColour::Magenta,
					ForegroundColour::Brown,
					ForegroundColour::LightGray,
					ForegroundColour::Gray,
					ForegroundColour::LightBlue,
					ForegroundColour::LightGreen,
					ForegroundColour::LightCyan,
					ForegroundColour::LightRed,
					ForegroundColour::LightMagenta,
					ForegroundColour::Yellow,
					ForegroundColour::White
			};
			
			return foregroundColours[rand() % 16];
		}
		
		BackgroundColour RandomBackground()
		{
			const static BackgroundColour backgroundColours[] = {
					BackgroundColour::Black,
					BackgroundColour::NavyBlue,
					BackgroundColour::Green,
					BackgroundColour::Teal,
					BackgroundColour::Maroon,
					BackgroundColour::Purple,
					BackgroundColour::Olive,
					BackgroundColour::Silver,
					BackgroundColour::Gray,
					BackgroundColour::Blue,
					BackgroundColour::Lime,
					BackgroundColour::Cyan,
					BackgroundColour::Red,
					BackgroundColour::Magenta,
					BackgroundColour::Yellow,
					BackgroundColour::White
			};
			
			return backgroundColours[rand() % 16];
		}
		
		void DrawTextCentered(Canvas& canvas, short y, std::string text, ForegroundColour colour)
		{
			canvas.DrawText((canvas.GetSize().X/2) - (text.length()/2),y,text, colour);
		}
		
	}//Utils
} // ConsoleGameEngine