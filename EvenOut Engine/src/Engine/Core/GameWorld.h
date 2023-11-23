#pragma once
#include "epch.h"
#include "Engine/Core/Object.h"
#include "Components.h"
#include "Engine/Core/Component.h"
#include "Engine/LogSystem/Log.h"

namespace Engine {
	class Rigidbody2D;
	class TransformComponent;

	class GameWorld {
	private:
		std::vector<std::shared_ptr<Object>> m_ObjectsInScene;

		b2Vec2 m_Gravity = b2Vec2(0.0f, -9.8f);
		b2World* m_WorldLevel;

	public:
		GameWorld() {}

		void Start();

		void Update(float deltaTime);

		void Draw();

		void Refresh();

/*
		template<typename T>
		std::vector<std::shared_ptr<Object>> FindObjectsOfType() {
			std::vector<std::shared_ptr<Object>> returnArray;
			for (auto& object : m_ObjectsInScene)
			{
				if (object->HasComponent<Rigidbody2D>()) {
					returnArray.push_back(object);
				}
			}

			return returnArray;
		}*/

		template <typename T, typename... TArgs>
		T* CreateActor(TArgs&& ...mArgs)
		{
			LOG_CORE("Created Actor", LOG_INFO);
			T* obj(new T(std::forward<TArgs>(mArgs)...));
			std::shared_ptr<Object> uPtr{ obj };
			m_ObjectsInScene.emplace_back(std::move(uPtr));

			obj->Start();

			if (uPtr->HasComponent<Rigidbody2D>())
			{
				auto& transform = uPtr->GetComponent<TransformComponent>();
				auto& rigidBody = uPtr->GetComponent<Rigidbody2D>();

				b2BodyDef bodyDef;

				switch (rigidBody.Type) {
				case Rigidbody2D::BodyType::Dynamic:
					bodyDef.type = b2_dynamicBody;
					break;
				case Rigidbody2D::BodyType::Static:
					bodyDef.type = b2_staticBody;
					break;
				case Rigidbody2D::BodyType::Kinematic:
					bodyDef.type = b2_kinematicBody;
					break;

				}

				bodyDef.position.Set(transform.Position.x, transform.Position.y);

				b2Body* body = m_WorldLevel->CreateBody(&bodyDef);
			}

			return obj;
		}

	};
}