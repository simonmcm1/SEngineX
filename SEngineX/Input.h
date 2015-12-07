//
//  Input.h
//  SEngineX
//
//  Created by Simon McMahon on 4/12/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Input__
#define __SEngineX__Input__

#include <iostream>
#include "Object.h"
#include <GLFW\glfw3.h>
#include <map>
#include <glm/vec2.hpp>


namespace SEngineX {
	
	enum class Key{UP = GLFW_KEY_UP, LEFT = GLFW_KEY_LEFT, DOWN = GLFW_KEY_DOWN, RIGHT = GLFW_KEY_RIGHT };
	enum class CursorMode{VISIBLE, DISABLED, HIDDEN};

	class Input {
		static std::map<Key, bool> keyPresses;
		static glm::vec2 mousePosition;
		//the delta from the latest mouse position callback
		static glm::vec2 mouseDelta;
		//sum of all deltas this past frame
		static glm::vec2 frameDelta;
		//save position for position coherency during single frame
		static glm::vec2 framePosition;
	public:
		static bool IsKeyDown(Key key);
		static void SetKeyDown(Key key, bool state);
		static glm::vec2 GetMousePosition();
		static glm::vec2 GetMouseDelta();
		static void SetMousePosition(float, float);
		static void ProcessEvents();
		static void SetCursorMode(CursorMode);
	};
}

#endif