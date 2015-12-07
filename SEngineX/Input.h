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
#include <vector>
#include <glm/vec2.hpp>


namespace SEngineX {

	enum class Key {
		UP = GLFW_KEY_UP, LEFT = GLFW_KEY_LEFT, DOWN = GLFW_KEY_DOWN, RIGHT = GLFW_KEY_RIGHT,
		W = GLFW_KEY_W, A = GLFW_KEY_A, S = GLFW_KEY_S, D = GLFW_KEY_D
	};

	enum class CursorMode { VISIBLE, DISABLED, HIDDEN };

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

	template<class T> class InputManager {
		InputManager<T>() {}
		std::map<T, std::vector<Key>> keyDefinitions;
	public:
		inline static InputManager<T>& Instance() {
			static InputManager<T> instance;
			return instance;
		}
		void AddMapping(T identifier, Key k) {
			keyDefinitions[identifier].push_back(k);
		}
		bool IsKeyDown(T identifier) {
			std::vector<Key> keys = keyDefinitions[identifier];
			for (std::vector<Key>::iterator it = keys.begin(); it != keys.end(); ++it) {
				if (Input::IsKeyDown(*it))
					return true;
			}
			return false;
		}


	};
}

#endif