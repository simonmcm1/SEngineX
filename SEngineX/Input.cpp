#include "Input.h"
#include "Engine.h"

std::map<SEngineX::Key, bool> SEngineX::Input::keyPresses;
glm::vec2 SEngineX::Input::mouseDelta;
glm::vec2 SEngineX::Input::mousePosition;
glm::vec2 SEngineX::Input::frameDelta;
glm::vec2 SEngineX::Input::framePosition;

bool SEngineX::Input::IsKeyDown(Key key)
{
	//hasn't been pressed yet at all
	if (keyPresses.count(key) == 0)
		return false;

	return keyPresses[key];
}

void SEngineX::Input::SetKeyDown(Key key, bool state)
{
	keyPresses[key] = state;
}

glm::vec2 SEngineX::Input::GetMousePosition()
{
	return framePosition;
}

glm::vec2 SEngineX::Input::GetMouseDelta()
{
	return frameDelta;
}

void SEngineX::Input::SetMousePosition(float x, float y)
{
	mouseDelta += glm::vec2(x - mousePosition.x, y - mousePosition.y);
	mousePosition = glm::vec2(x, y);	
}

void SEngineX::Input::ProcessEvents()
{
	frameDelta = mouseDelta;
	framePosition = mousePosition;

	//reset delta counter
	mouseDelta = glm::vec2();
}

void SEngineX::Input::SetCursorMode(CursorMode mode)
{
	int glfwMode = GLFW_CURSOR_NORMAL;
	switch (mode) {
	case CursorMode::DISABLED:
		glfwMode = GLFW_CURSOR_DISABLED;
		break;
	case CursorMode::HIDDEN:
		glfwMode = GLFW_CURSOR_HIDDEN;
		break;
	case CursorMode::VISIBLE:
		glfwMode = GLFW_CURSOR_NORMAL;
		break;
	}
	glfwSetInputMode(SEngineX::Engine::Instance().window, GLFW_CURSOR, glfwMode);
}


