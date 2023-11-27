#include "epch.h"
#include "Input.h"

namespace Engine {
	SDL_Gamepad* Input::m_Pad;

	void Input::SendGamepad(SDL_Gamepad* controller)
	{ 
		m_Pad = controller;
	}

	bool Input::IsGamepadButtonPressed(SDL_GamepadButton button)
	{
		//std::this_thread::sleep_for(0.1s);
		if (SDL_GetGamepadButton(m_Pad, button) != 0) {
			return true;
		}
		else {
			return false;
		}
	}

	float Input::GetGamepadAxis(SDL_GamepadAxis axis)
	{
		Sint16 value = SDL_GetGamepadAxis(m_Pad, axis);

		return value = std::clamp((float)value, -1.0f, 1.0f);
	}
}
