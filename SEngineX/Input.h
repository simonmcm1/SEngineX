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


namespace SEngineX {
	
	enum class Key{UP = GLFW_KEY_UP, LEFT = GLFW_KEY_LEFT, DOWN = GLFW_KEY_DOWN, RIGHT = GLFW_KEY_RIGHT };

	class Input {
		static std::map<Key, bool> keyPresses;
	public:
		static bool IsKeyDown(Key key);
		static void SetKeyDown(Key key, bool state);
	};
}

#endif