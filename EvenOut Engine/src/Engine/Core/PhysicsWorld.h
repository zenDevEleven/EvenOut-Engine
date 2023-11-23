#pragma once
#include "epch.h"
#include "Engine/Core/GameWorld.h"
#include "Engine/Core/Components.h"
#include "Engine/Log/Log.h"

namespace Engine {
	class PhysicsWorld 
	{

	public:
		PhysicsWorld() = default;
		PhysicsWorld(GameWorld* world) : m_World(world) {};

		virtual ~PhysicsWorld() 
		{
			delete m_WorldLevel;
			m_WorldLevel = nullptr;
		};
		
		b2World* GetWorld() { return m_WorldLevel; }

/*		b2BodyType Body2DTypeToBox2DBody(Rigidbody2D::BodyType bodyType);*/
		
		/*void TryCreateBody(Object* actor);*/

		void Start();

		void Update(float deltaTime);

		void Draw() {}

	private:
		const int32_t velocityInterations = 6;
		const int32_t positionInterations = 2;

		b2Vec2 m_Gravity = b2Vec2(0.0f, -9.8f);
		b2World* m_WorldLevel;
		GameWorld* m_World;


	};

}