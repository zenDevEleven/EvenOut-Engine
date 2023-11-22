#pragma once
#include "epch.h"
#include "Engine/Core/Component.h"
#include "Engine/Core/Object.h"

namespace Engine {
	class Object;
	class Component;

	using ComponentID = std::size_t;

	inline ComponentID GetComponentTypeID() {
		static ComponentID m_lastID = 0;

		return m_lastID++;
	}

	template <typename T>
	inline ComponentID GetComponentTypeID() noexcept
	{
		static ComponentID m_typeID = GetComponentTypeID();
		return m_typeID;
	}

	constexpr std::size_t maxComponents = 32;

	using ComponentBitSet = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;

	class Component {
	public:
		Object* m_Actor;
		Component() {}
		virtual ~Component() {}

		virtual void Start() {}
		virtual void Update(float deltaTime) {}
		virtual void DrawComponent() {}
	};
}