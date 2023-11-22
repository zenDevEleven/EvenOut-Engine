#include "Player.h"
using Frame = Engine::AnimatorComponent::AnimationFrame;

Player::Player()
{
	m_Transform = AddComponent<Engine::TransformComponent>();
	m_SpriteRenderer = AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/Ship1.bmp", 64);
	m_Animator = AddComponent<Engine::AnimatorComponent>(m_SpriteRenderer.m_SpriteTexture);

	m_Animator.SetStartFrame(Frame(4, 1));
}

void Player::Start()
{
	
}

void Player::Update(float deltaTime)
{
	
}