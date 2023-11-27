#include "epch.h"
#include "PhysicsWorld.h"
#include "Engine/Core/Components.h"

namespace Engine {

	PhysicsWorld* PhysicsWorld::m_Instance;

	PhysicsWorld::PhysicsWorld() {
		m_Instance = this;
		m_WorldLevel = new b2World(m_Gravity);
	}

	void PhysicsWorld::Update(float deltaTime) 
	{
		const int32_t velocityInterations = 6;
		const int32_t positionInterations = 2;

		m_WorldLevel->Step(deltaTime, velocityInterations, positionInterations);

		for (auto& object : m_World->GetObjects()) {

			if (object->HasComponent<Rigidbody2D>()) {
				auto& transform = object->GetComponent<TransformComponent>();
				auto& body2d = object->GetComponent<Rigidbody2D>();

				b2Body* body = (b2Body*)body2d.RuntimeBody;
				const auto& position = body->GetPosition();
				transform.Translate(position.x * 100, position.y * 100);
			}
		}
	}

	b2Body* PhysicsWorld::CreateBody(b2BodyDef body)
	{
		LOG_CORE("Created Physics Body", LOG_INFO);
		return m_WorldLevel->CreateBody(&body);
	}

	void PhysicsWorld::SetWorld(GameWorld* world)
	{
		m_World = world;
	}
}
