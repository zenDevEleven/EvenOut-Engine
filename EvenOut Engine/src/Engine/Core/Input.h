#pragma once
#include "epch.h"

namespace Engine {
	class Input {
	public:
		static void SendGamepad(SDL_Gamepad* controller);
	private:
		static SDL_Gamepad* m_Pad;
	};
}