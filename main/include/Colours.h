//
// Created by Henry on 13/11/2022.
//

#ifndef CONSOLEGAMEENGINEPLUSPLUS_COLOURS_H
#define CONSOLEGAMEENGINEPLUSPLUS_COLOURS_H

#include <cstdint>
#include <cstdlib>

namespace ConsoleGameEngine
{
	enum class ForegroundColour
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		Gray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};
	
	enum class BackgroundColour
	{
		Black = 0,
		NavyBlue = 16,
		Green = 32,
		Teal = 48,
		Maroon = 64,
		Purple = 80,
		Olive = 96,
		Silver = 112,
		Gray = 128,
		Blue = 144,
		Lime = 160,
		Cyan = 176,
		Red = 192,
		Magenta = 208,
		Yellow = 224,
		White = 240
	};
	
	enum class PixelType
	{
		Full = 219,
		ThreeQuarter = 178,
		Half = 177,
		Quarter = 176,
		None = 255
	};
}

#endif //CONSOLEGAMEENGINEPLUSPLUS_COLOURS_H
