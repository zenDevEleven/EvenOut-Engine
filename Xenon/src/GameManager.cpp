#include "GameManager.h"
#include "Background.h"

;void GameManager::Start()
{
	LOG_APP("Start", Engine::LOG_INFO);
	m_World.CreateActor<Background>();
	player = m_World.CreateActor<Player>();
}

void GameManager::Update(float deltaTime)
{
	
}