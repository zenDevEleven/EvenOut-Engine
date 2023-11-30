#include "epch.h"
#include "GameEngine.h"
#include "Engine/Core/GameWorld.h"
#include "Engine/Core/PhysicsWorld.h"

namespace Engine {

	GameEngine* GameEngine::m_Instance;

	GameEngine::GameEngine()
	{
		m_Instance = this;
	}

	GameEngine::~GameEngine()
	{

	}

	void GameEngine::Initialize(const char* title, int width, int height)
	{

		LOG_CORE(std::format("Initializing Window({0}, {1})", width, height).c_str(), LOG_INFO);

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) != 0) {
			LOG_CORE("SDL Initialized", LOG_INFO);
		}

		m_Window = SDL_CreateWindow(title, width, height, 0);


		Renderer::Init(m_Window);

		m_World = new GameWorld();
		m_PhysicsWorld = new PhysicsWorld();
		m_PhysicsWorld->SetWorld(m_World);
	
	}

	void GameEngine::HandleEvents()
	{
		while (SDL_PollEvent(&m_GamepadEvent))
		{
			switch (m_GamepadEvent.type) 
			{
			case SDL_EVENT_GAMEPAD_ADDED:
				m_ID = m_GamepadEvent.gdevice.which;
				m_Controller = SDL_OpenGamepad(m_GamepadEvent.gdevice.which);
				LOG_CORE("Controller: " + std::string(SDL_GetGamepadInstanceName(m_GamepadEvent.gdevice.which)), LOG_INFO);
				Input::SendGamepad(m_Controller);
				break;
			case SDL_EVENT_QUIT:
				isRunning = false;
				break;
			}
		}
	}

	void GameEngine::Run()
	{
		isRunning = true;
		while (isRunning) {
			m_Time = (float)SDL_GetTicks();
			float deltaTime = (m_Time - m_PreviousTime) / 1000.0f;
			m_PreviousTime = m_Time;
			
			m_FrameTime += deltaTime;

			HandleEvents();
			m_World->Refresh();
			m_PhysicsWorld->Update(deltaTime);
			m_World->Update(deltaTime);

			Render();
		}

		Clean();
	}

	void GameEngine::Render()
	{
		SDL_RenderClear(Renderer::GetRenderer());
		m_World->Draw();
		SDL_RenderPresent(Renderer::GetRenderer());
	}

	void GameEngine::Clean()
	{
		SDL_DestroyWindow(m_Window);
		SDL_DestroyRenderer(Renderer::GetRenderer());
		SDL_Quit();
		LOG_CORE("Engine cleaned!", LOG_INFO);
	}

	bool GameEngine::IsRunning()
	{
		return isRunning;
	}

}