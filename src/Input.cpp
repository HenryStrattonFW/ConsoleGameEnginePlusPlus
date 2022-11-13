//
// Created by Henry on 13/11/2022.
//

#include <Windows.h>
#include <map>
#include "../include/Input.h"

namespace ConsoleGameEngine
{
	namespace Input
	{
		struct InputFrame
		{
			std::map<unsigned short, bool> keyStates={};
			DWORD mouseButtons = 0;
			COORD mousePosition = {0,0};
		};
		
		InputFrame currentFrame;
		InputFrame previousFrame;
		
		
		void SwapFrames(struct InputFrame *a, struct InputFrame *b)
		{
			struct InputFrame temp = *a;
			*a = *b;
			*b = temp;
		}
		
		void Update(HANDLE readHandle)
		{
			SwapFrames(&currentFrame, &previousFrame);
			currentFrame.keyStates.clear();
			
			DWORD eventCount;
			GetNumberOfConsoleInputEvents(readHandle, &eventCount);
			
			if(eventCount == 0)
				return;
			
			DWORD numEventsRead = 0;
			INPUT_RECORD *eventBuffer;
			eventBuffer = new INPUT_RECORD[eventCount];
			ReadConsoleInput(readHandle, eventBuffer, eventCount, &numEventsRead);
			
			for(DWORD i=0;i<numEventsRead;i++)
			{
				switch (eventBuffer[i].EventType)
				{
					case KEY_EVENT:
						currentFrame.keyStates.insert({eventBuffer[i].Event.KeyEvent.wVirtualKeyCode, true});
						break;
					case MOUSE_EVENT:
						currentFrame.mouseButtons = eventBuffer[i].Event.MouseEvent.dwButtonState;
						currentFrame.mousePosition = eventBuffer[i].Event.MouseEvent.dwMousePosition;
						break;
					default:
						// Some event types are not handled because we just don't care.
						// For example, window resize, which we currently don't allow.
						break;
				}
			}
			delete eventBuffer;
		}
		
		
		bool CheckForKey(InputFrame &frame, unsigned short key)
		{
			if (frame.keyStates.count(key) == 0) return false;
			return frame.keyStates[key];
		}
		
		bool IsKeyDown(unsigned short key)
		{
			return CheckForKey(currentFrame, key);
		}
		
		bool WasKeyPressed(unsigned short key)
		{
			return CheckForKey(currentFrame, key) &&
				   !CheckForKey(previousFrame, key);
		}
		
		bool WasKeyReleased(unsigned short key)
		{
			return !CheckForKey(currentFrame, key) &&
				   CheckForKey(previousFrame, key);
		}
		
		bool MouseButtonDown(MouseButton button)
		{
			return (currentFrame.mouseButtons & static_cast<DWORD>(button)) != 0;
		}
		
		bool MouseButtonPressed(MouseButton button)
		{
			return ((currentFrame.mouseButtons & static_cast<DWORD>(button)) != 0 &&
				   (previousFrame.mouseButtons & static_cast<DWORD>(button)) == 0);
		}
		
		bool MouseButtonReleased(MouseButton button)
		{
			return ((previousFrame.mouseButtons & static_cast<DWORD>(button)) != 0 &&
					(currentFrame.mouseButtons & static_cast<DWORD>(button)) == 0);
		}
		
	} // Input
} //ConsoleGameEngine