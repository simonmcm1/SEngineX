#include "Input.h"

std::map<SEngineX::Key, bool> SEngineX::Input::keyPresses;

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