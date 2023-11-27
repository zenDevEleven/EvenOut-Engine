#pragma once
#include "Engine/Core/Object.h"
#include "Engine/LogSystem/Log.h"

namespace Engine {
	
	class GameWorld {
	protected:
		std::vector<std::shared_ptr<Object>> m_ObjectsInScene;

	public:
		GameWorld() {};
		virtual ~GameWorld() { std::cout << "Destroyed!" << std::endl; };

		void Start();

		void Update(float deltaTime);


		void Draw();

		void Refresh();

		std::vector<std::shared_ptr<Object>> GetObjects() { return m_ObjectsInScene; }

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