#include "epch.h"
#include "Input.h"

namespace Engine {
	SDL_Gamepad* Input::m_Pad;

	void Input::SendGamepad(SDL_Gamepad* controller)
	{
		m_Pad = controller;
	}
}
