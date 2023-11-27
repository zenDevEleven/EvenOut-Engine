#include "GameManager.h"
#include "Background.h"
#include "ParallaxBG.h"

GameManager* GameManager::m_Instance;

GameManager::GameManager()
{
	m_Instance = this;
}
void GameManager::Start()
{
	LOG_APP("Start", Engine::LOG_INFO);
	m_World.CreateActor<Background>();
	m_World.CreateActor<ParallaxBG>();

	player = m_World.CreateActor<Player>();
}

void GameManager::Update(float deltaTime)
{
	
}