#pragma once
#include "Engine/Core/Actor.h"
#include "Engine/Core/Components.h"
#include "Engine/Core/Component.h"
#include "Engine/Core/Input.h"

class Player : public Engine::Actor
{
public:
	Player();
	virtual ~Player() {}
	void Start() override;
	void Update(float deltaTime) override;
private:
	Engine::TransformComponent* m_Transform;
	Engine::SpriteRenderer2D* m_SpriteRenderer;
	Engine::AnimatorComponent* m_Animator;
 	Engine::Rigidbody2D* m_RigidBody2d;

	float m_FireRate = 3.0f;
	float m_NexShotTime = 0.0f;
	float m_CurrentTime = 0.0f;

	float lastX = -2;

};

