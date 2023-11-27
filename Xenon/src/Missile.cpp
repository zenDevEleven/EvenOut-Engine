#include "Missile.h"

using Frame = Engine::AnimatorComponent::AnimationFrame;

Missile::Missile(float missileSpeed, glm::vec2 spawnPos)
{
	m_MissileSpeed = missileSpeed;

	m_Transform = &AddComponent<Engine::TransformComponent>(spawnPos);
	m_SpriteRenderer = &AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/missile.bmp", 16, 2);
	m_Animator = &AddComponent<Engine::AnimatorComponent>(m_SpriteRenderer->m_SpriteTexture);
}

void Missile::Start()
{
	__super::Start();

	m_Animator->SetStartFrame(Frame(1, 1));
}

void Missile::Update(float deltaTime)
{
	__super::Update(deltaTime);

	m_Transform->AddPos(0, -m_MissileSpeed * deltaTime);
}
