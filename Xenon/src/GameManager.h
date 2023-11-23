#pragma once
#include "Engine/Core/Actor.h"
#include "Engine/Core/GameWorld.h"
#include "Engine/Core/GameEngine.h"
#include "Engine/LogSystem/Log.h"
#include "Player.h"

class GameManager : public Engine::Actor
{
public:
	GameManager() {};
	~GameManager() {};

	void Start() override;
	void Update(float deltaTime) override;
private:
	Engine::GameWorld& m_World = Engine::GameEngine::GetEngine()->GetWorld();
	Player* player;
};

