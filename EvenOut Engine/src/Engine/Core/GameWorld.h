#pragma once
#include "Engine/Core/Object.h"
#include "Engine/Core/Component.h"
#include "Engine/Core/Components.h"
#include "Engine/LogSystem/Log.h"

namespace Engine {

	class GameWorld {
	private:
		std::vector<std::shared_ptr<Object>> m_ObjectsInScene;

		//b2Vec2 m_Gravity = b2Vec2(0.0f, -9.8f);
		//b2World* m_WorldLevel;

	public:
		GameWorld() {};

		//b2World* GetPhysicsWorld() { return m_WorldLevel; }

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

			return obj;
		}

	};
}