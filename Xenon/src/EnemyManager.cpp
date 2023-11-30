#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "Global.h"
#include "GameManager.h"

#include "Engine/LogSystem/Log.h"
#include <random>

#include "BigAsteroid.h"
#include "SmallAsteroid.h"
#include "MediumAsteroid.h"

EnemyManager* EnemyManager::m_instance;

glm::vec2 FindRandomSpawnLocation() 
{
	std::random_device rd;
	std::uniform_real_distribution<double> dist(20.0, (double)Global::WIDTH - 20);
	
	double value = dist(rd);
	std::cout << "VALUE: " << value << std::endl;

	return glm::vec2(value, -70);

}

void EnemyManager::Start()
{
	m_instance = this;
	SpawnAsteroids("Assets/Textures/SAster96.bmp", 2, 20.0f, 640.0f, -70.0f, -60.0f, AsteroidsSize::LARGE);
}

void EnemyManager::Update(float deltaTime)
{
	m_Time += deltaTime;
	if(Engine::Input::IsGamepadButtonPressed(SDL_GAMEPAD_BUTTON_SOUTH, true))
		SpawnDrones(8, m_Time);
}

void EnemyManager::Draw()
{
	
}

void EnemyManager::SpawnDrones(int numberOfDrones, int time)
{
	glm::vec2 startPos = FindRandomSpawnLocation();
	float offsetY = 0;
	for (size_t i = 0; i < numberOfDrones; ++i)
	{
		GameManager::GetManager().InstantiateObject<EnemyDrone>(startPos.x, startPos.y + offsetY);

		offsetY += 32;
	}
}

void EnemyManager::SpawnAsteroids(const char* filepath, int numberOfAsteroids, float minX, float maxX, float minY, float maxY, AsteroidsSize type)
{
	for (size_t i = 0; i < numberOfAsteroids; ++i)
	{
		float x = GameManager::GetManager().RandomNumber<float>(minX, maxX);
		float y = GameManager::GetManager().RandomNumber<float>(minY, maxY);

		switch (type)
		{

		case SMALL:
			GameManager::GetManager().InstantiateObject<SmallAsteroid>(filepath, x, y);
			break;
		case MEDIUM:
			GameManager::GetManager().InstantiateObject<MediumAsteroid>(filepath, x, y);
			break;		
		case LARGE:
			GameManager::GetManager().InstantiateObject<BigAsteroid>(filepath, x, y);
			break;
		}
	}
}

void EnemyManager::OnContactEvent(Object* other)
{
	
}

void EnemyManager::OnEndContactEvent(Object* other)
{
	
}
