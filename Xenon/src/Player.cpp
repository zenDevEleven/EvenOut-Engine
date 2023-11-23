#include "Player.h"
using Frame = Engine::AnimatorComponent::AnimationFrame;

Player::Player()
{
	m_Transform = &AddComponent<Engine::TransformComponent>();
	m_SpriteRenderer = &AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/Ship1.bmp", 64);
	m_Animator = &AddComponent<Engine::AnimatorComponent>(m_SpriteRenderer->m_SpriteTexture);
	m_Animator = &AddComponent<Engine::AnimatorComponent>(m_SpriteRenderer->m_SpriteTexture);
	m_RigidBody2d = &AddComponent<Engine::Rigidbody2D>();
}

void Player::Start()
{
	__super::Start();

	m_Animator->SetStartFrame(Engine::AnimatorComponent::AnimationFrame(4, 1));

	m_Animator->CreateAnimation
	(new Engine::AnimatorComponent::Animation("SpaceshipRight", std::vector<Engine::AnimatorComponent::AnimationFrame> {
			Frame(5, 1),
			Frame(6, 1),
			Frame(7, 1)
	}));

	m_Animator->CreateAnimation
	(new Engine::AnimatorComponent::Animation("IdleFromRight", std::vector<Engine::AnimatorComponent::AnimationFrame> {
		Engine::AnimatorComponent::AnimationFrame(7, 1),
			Frame(6, 1),
			Frame(5, 1),
			Frame(4, 1)
	}));

	m_Animator->CreateAnimation
	(new Engine::AnimatorComponent::Animation("IdleFromLeft", std::vector<Engine::AnimatorComponent::AnimationFrame> {
		Engine::AnimatorComponent::AnimationFrame(1, 1),
			Frame(2, 1),
			Frame(3, 1),
			Frame(4, 1)
	}));

	m_Animator->CreateAnimation
	(new Engine::AnimatorComponent::Animation("SpaceshipLeft", std::vector<Engine::AnimatorComponent::AnimationFrame> {
			Frame(3, 1),
			Frame(2, 1),
			Frame(1, 1),
	}));
}

void Player::Update(float deltaTime)
{
	__super::Update(deltaTime);

	float XAxis = Engine::Input::GetGamepadAxis(SDL_GAMEPAD_AXIS_LEFTX);
	float YAxis = Engine::Input::GetGamepadAxis(SDL_GAMEPAD_AXIS_LEFTY);

	if (XAxis > 0) {
		m_Animator->PlayAnimation("SpaceshipRight", 0.02, deltaTime, false);
		lastX = XAxis;
	}
	else if (XAxis < 0) {
		m_Animator->PlayAnimation("SpaceshipLeft", 0.02, deltaTime, false);
		lastX = XAxis;
	}
	else if (XAxis == 0) {
		if (lastX == 1)
			m_Animator->PlayAnimation("IdleFromRight", 0.02, deltaTime, false);
		else
			m_Animator->PlayAnimation("IdleFromLeft", 0.02, deltaTime, false);
	}

	m_Transform->Translate(XAxis * 7.0f, YAxis * 7.0f );
}