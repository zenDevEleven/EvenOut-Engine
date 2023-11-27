#pragma once
#include "Engine/Core/Object.h"
#include "Engine/Core/Components.h"

class ParallaxBG : public Engine::Object
{
public:
	ParallaxBG() {}

	void Start() override;

	void Update(float deltaTime) override;

private:
	float m_ScollingSpeed = 20.0f;

	Engine::SpriteRenderer2D* m_SpriteRenderer;
	Engine::TransformComponent* m_Transform;
};

