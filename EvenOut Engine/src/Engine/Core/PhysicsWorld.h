#pragma once
#include "epch.h"
#include "Engine/Core/GameWorld.h"

namespace Engine {


	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld() {};
		void Update(float deltaTime);

		b2Body* CreateBody(b2BodyDef body);

		static PhysicsWorld& GetPhysicsWorld() { return *m_Instance; }
		GameWorld& GetWorld() { return *m_World; }

		void SetWorld(GameWorld* world);

	private:
		static PhysicsWorld* m_Instance;

		GameWorld* m_World;

		b2Vec2 m_Gravity = b2Vec2(0.0f, 9.8f);
		b2World* m_WorldLevel;
	};
}

