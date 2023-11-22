#pragma once
#include "Engine/Log/Log.h"
#include "Engine/Core/GameWorld.h"

namespace Engine {

	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void Initialize(const char* title, int width, int height);

		void HandleEvents();
		void Run();
		void Render();
		void Clean();

		bool IsRunning();

		inline static GameEngine* GetEngine() { return m_Instance; };
		inline GameWorld& GetWorld() { return *m_World; }

	private:
		static GameEngine* m_Instance;

		float m_PreviousTime = 0;
		float m_Time = 0;

		bool isRunning = false;

		int m_WindowWidth = 0;
		int m_WindowHeight = 0;

		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;

		SDL_Event m_GamepadEvent;
		SDL_Gamepad* m_Controller;
		SDL_JoystickID m_ID;

		std::unique_ptr<GameWorld> m_World;
	};
}

