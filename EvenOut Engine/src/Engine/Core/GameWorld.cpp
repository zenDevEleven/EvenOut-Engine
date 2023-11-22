#include "epch.h"
#include "GameWorld.h"

namespace Engine {
	void GameWorld::UpdateObjects(float deltaTime)
	{
		for (int i = 0; i < m_ObjectsInScene.size(); i++)
		{
			m_ObjectsInScene[i]->Update(deltaTime);
		}
	}
}
