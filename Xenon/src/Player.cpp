#include "Player.h"
#include "Missile.h"
#include "GameManager.h"
#include "Engine/LogSystem/Log.h"

using Frame = Engine::AnimatorComponent::AnimationFrame;

Player::Player()
{
	m_Transform = &AddComponent<Engine::TransformComponent>(glm::vec2(600.0f, 400.0f));
	m_SpriteRenderer = &AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/Ship1.bmp", 64);
	m_Animator = &AddComponent<Engine::AnimatorComponent>(m_SpriteRenderer->m_SpriteTexture);
	m_RigidBody2d = &AddComponent<Engine::Rigidbody2D>(Engine::Rigidbody2D::BodyType::Dynamic);
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

	m_CurrentTime += deltaTime;

	float XAxis = Engine::Input::GetGamepadAxis(SDL_GAMEPAD_AXIS_LEFTX);
	float YAxis = Engine::Input::GetGamepadAxis(SDL_GAMEPAD_AXIS_LEFTY);


	if (Engine::Input::IsGamepadButtonPressed(SDL_GAMEPAD_BUTTON_NORTH)) {
		LOG_APP("Pressed Missile", Engine::LOG_INFO);
		if (m_NexShotTime < m_CurrentTime) {
			m_NexShotTime = m_CurrentTime + m_FireRate;
			GameManager::GetManager().GetWorld().CreateActor<Missile>(250.0f, glm::vec2(m_Transform->Position.x + 24, m_Transform->Position.y - 30));
			GameManager::GetManager().GetWorld().CreateActor<Missile>(270.0f, glm::vec2(m_Transform->Position.x + 24, m_Transform->Position.y - 30));
			GameManager::GetManager().GetWorld().CreateActor<Missile>(280.0f, glm::vec2(m_Transform->Position.x + 24, m_Transform->Position.y - 30));
			GameManager::GetManager().GetWorld().CreateActor<Missile>(300.0f, glm::vec2(m_Transform->Position.x + 24, m_Transform->Position.y - 30));
			GameManager::GetManager().GetWorld().CreateActor<Missile>(310.0f, glm::vec2(m_Transform->Position.x + 24, m_Transform->Position.y - 30));
		}
	}

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

	m_Transform->AddPos(XAxis * 20.0f, YAxis * 20.0f );
}
