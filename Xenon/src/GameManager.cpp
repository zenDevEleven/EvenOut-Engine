#include "GameManager.h"
#include "Background.h"
#include "ParallaxBG.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "DestructionParticle.h"
#include "PowerUp.h"


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

	m_World.CreateActor<EnemyManager>();
	m_World.CreateActor<PowerUp>(PowerUpType::MISSILE_PU, glm::vec2(200.0f, 200.0f));


	player = m_World.CreateActor<Player>();

}

void GameManager::Update(float deltaTime)
{
	
}

void GameManager::OnContactEvent(Object* other)
{
	
}

void GameManager::OnEndContactEvent(Object* other)
{
	
}
