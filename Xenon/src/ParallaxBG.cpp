#include "ParallaxBG.h"

void ParallaxBG::Start()
{
	__super::Start();

	m_Transform = &AddComponent<Engine::TransformComponent>();
	m_SpriteRenderer = &AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/rocks.bmp", glm::vec2(640, 480));
}

void ParallaxBG::Update(float deltaTime)
{
	__super::Update(deltaTime);
	m_Transform->AddPos(0, m_ScollingSpeed * deltaTime);
}
