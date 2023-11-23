#pragma once
#include "Engine/Core/Component.h"
#include "Engine/LogSystem/Log.h"

namespace Engine {
	class Component;

	class Object
	{
	private:
		bool m_Active = true;

		std::vector<std::unique_ptr<Component>> m_Components;

		ComponentArray m_ComponentArray;
		ComponentBitSet m_ComponentBitSet;

	public:

		Object() = default;

		virtual ~Object() {

		}

		virtual void Start() 
		{
			for (auto& c : m_Components) {
				c->Start();
			}
		}

		virtual void Update(float deltaTime) 
		{
			for (auto& c : m_Components) {
				c->UpdateComponent(deltaTime);
			}
		}

		virtual void Draw()
		{
			for (auto& c : m_Components) {
				c->DrawComponent();
			}
		}

		bool IsActive() const { return m_Active; }
		void Destroy() { m_Active = false; }

		template<typename T>
		bool HasComponent() const{
			return m_ComponentBitSet[GetComponentTypeID<T>()];
		}

		template<typename T, typename... TArgs>
		T& AddComponent(TArgs&&... Margs) 
		{
			T* component(new T(std::forward<TArgs>(Margs)...));

			component->m_Actor = this;

			std::unique_ptr<Component>uPtr{ component };

			m_Components.emplace_back(std::move(uPtr));

			m_ComponentArray[GetComponentTypeID<T>()] = component;
			m_ComponentBitSet[GetComponentTypeID<T>()] = true;

			component->Start();
			return *component;
		}

		template<typename T> 
		T& GetComponent() const{
			auto ptr(m_ComponentArray[GetComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}


	};
}

