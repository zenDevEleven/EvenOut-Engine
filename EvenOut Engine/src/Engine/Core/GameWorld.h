#pragma once
#include "epch.h"
#include "Engine/Core/Object.h"
#include "Engine/Core/Components.h"
#include "Engine/Log/Log.h"

namespace Engine {
	class GameWorld {
	private:
		std::vector<std::unique_ptr<Object>> m_ObjectsInScene;
	public:
		GameWorld() {}

		void Start() {
			for (auto& object : m_ObjectsInScene) object->Start();
		}

		void Update(float deltaTime) {
			for (auto& object : m_ObjectsInScene) {

				object->Update(deltaTime);
				
			}
		}

		void UpdateObjects(float deltaTime);

		void Draw() {

			for (auto& object : m_ObjectsInScene)
			{
				object->Draw();
			}
			
		}

		void Refresh() {

			m_ObjectsInScene.erase(std::remove_if(std::begin(m_ObjectsInScene), std::end(m_ObjectsInScene),
				[](const std::unique_ptr<Object>& mObject)
				{
					return !mObject->IsActive();
				}), std::end(m_ObjectsInScene));
			
		}

		template <typename T, typename... TArgs>
		T* CreateActor(TArgs&& ...mArgs)
		{
			LOG_CORE("Created Actor", LOG_INFO);
			T* obj(new T(std::forward<TArgs>(mArgs)...));
			std::unique_ptr<Object> uPtr{ obj };
			m_ObjectsInScene.emplace_back(std::move(uPtr));
			//obj->AddComponent<TransformComponent>();

			obj->Start();

			return obj;
		}

	};
}