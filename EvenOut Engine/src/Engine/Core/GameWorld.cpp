#include "epch.h"
#include "GameWorld.h"

namespace Engine 
{
	void GameWorld::Start()
	{
		for (auto& object : m_ObjectsInScene) object->Start();
	}

	void GameWorld::Update(float deltaTime)
	{
		for (auto& object : m_ObjectsInScene) 
		{
			object->Update(deltaTime);
		}
	}

	void GameWorld::Draw()
	{

		for (auto& object : m_ObjectsInScene)
		{
			object->Draw();
		}

	}

	void GameWorld::Refresh()
	{

		m_ObjectsInScene.erase(std::remove_if(std::begin(m_ObjectsInScene), std::end(m_ObjectsInScene),
			[](const std::shared_ptr<Object>& mObject)
			{
				return !mObject->IsActive();
			}), std::end(m_ObjectsInScene));

	}
}