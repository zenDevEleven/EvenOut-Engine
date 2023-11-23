#include "epch.h"
#include "GameWorld.h"

namespace Engine 
{
	void GameWorld::Start()
	{
		/*m_WorldLevel = new b2World(m_Gravity);*/
		for (auto& object : m_ObjectsInScene) object->Start();
	}

	void GameWorld::Update(float deltaTime)
	{
		//physics
/*
		const int32_t velocityInterations = 6;
		const int32_t positionInterations = 2;

		m_WorldLevel->Step(deltaTime, velocityInterations, positionInterations);

		for (auto& object : m_ObjectsInScene) {

			auto& transform = object->GetComponent<TransformComponent>();
			auto& body2d = object->GetComponent<Rigidbody2D>();

			b2Body* body = (b2Body*)body2d.RuntimeBody;
			const auto& position = body->GetPosition();
			transform.Translate(position.x, position.y);
		}*/

		for (auto& object : m_ObjectsInScene) {

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