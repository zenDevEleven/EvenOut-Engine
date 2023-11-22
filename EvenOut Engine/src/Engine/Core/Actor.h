#pragma once
#include "Engine/Core/Object.h"

namespace Engine {
	class Actor : public Object
	{
	public:
		Actor();
		virtual ~Actor();


		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;
	};
}