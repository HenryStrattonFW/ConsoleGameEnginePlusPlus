//
// Created by Henry on 13/11/2022.
//

#include <Windows.h>
#include <map>
#include "../../include/core/Input.h"

namespace ConsoleGameEngine
{
	namespace Input
	{
		std::map<unsigned short, bool> keyStates={};
		std::map<unsigned short, bool> changed={};
		DWORD prevMouseButtons = 0;
		DWORD mouseButtons = 0;
		COORD mousePosition = {0,0};
		
		void Update(HANDLE readHandle)
		{
			prevMouseButtons = mouseButtons;
			changed.clear();
			
			
			DWORD eventCount;
			GetNumberOfConsoleInputEvents(readHandle, &eventCount);
			if(eventCount == 0)
				return;
			
			// Read in all the events.
			DWORD numEventsRead = 0;
			INPUT_RECORD *eventBuffer = new INPUT_RECORD[eventCount];
			ReadConsoleInput(readHandle, eventBuffer, eventCount, &numEventsRead);
			
			// Process the events, extract only what we care about.
			for(DWORD i=0;i<numEventsRead;i++)
			{
				unsigned short code=0;
				switch (eventBuffer[i].EventType)
				{
					case KEY_EVENT:
						code = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
						if (code == MAPVK_VK_TO_CHAR)
						{
							code = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
						}
						keyStates.insert_or_assign(code, eventBuffer[i].Event.KeyEvent.bKeyDown);
						changed.insert({code, true});
						//TODO: Work our an approach that handles character keys, virtual key codes don't map them all.
						break;
					case MOUSE_EVENT:
						mouseButtons = eventBuffer[i].Event.MouseEvent.dwButtonState;
						mousePosition = eventBuffer[i].Event.MouseEvent.dwMousePosition;
						break;
					default:
						// Some event types are not handled because we just don't care.
						// For example, window resize, which we currently don't allow.
						break;
				}
			}
			delete[] eventBuffer;
		}
		
		bool IsKeyDown(unsigned short key)
		{
			if (keyStates.count(key) == 0) return false;
			return keyStates[key];
		}
		
		bool WasKeyPressed(unsigned short key)
		{
			if (changed.count(key) == 0) return false;
			return IsKeyDown(key);
		}
		
		bool WasKeyReleased(unsigned short key)
		{
			if (changed.count(key) == 0) return false;
			return !IsKeyDown(key);
		}
		
		bool MouseButtonDown(MouseButton button)
		{
			return (mouseButtons & static_cast<DWORD>(button)) != 0;
		}
		
		bool MouseButtonPressed(MouseButton button)
		{
			return (mouseButtons & static_cast<DWORD>(button) != 0) &&
					(prevMouseButtons & static_cast<DWORD>(button) == 0);
		}
		
		bool MouseButtonReleased(MouseButton button)
		{
			return (mouseButtons & static_cast<DWORD>(button) == 0) &&
				   (prevMouseButtons & static_cast<DWORD>(button) != 0);
		}
		
		COORD MousePosition()
		{
			return mousePosition;
		}
		
	} // Input
} //ConsoleGameEngine