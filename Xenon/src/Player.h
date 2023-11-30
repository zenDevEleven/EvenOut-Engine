#pragma once
#include "Engine/Core/Actor.h"
#include "Engine/Core/Components.h"
#include "Engine/Core/Component.h"
#include "Engine/Core/Input.h"
#include "Missile.h"

class Player : public Engine::Actor
{
public:
	Player();
	virtual ~Player() {}
	void Start() override;
	void Update(float deltaTime) override;

	void UpgradeMissileTier();

	void OnContactEvent(Object* other) override;
	void OnEndContactEvent(Object* other) override;

private:
	Engine::TransformComponent* m_Transform;
	Engine::SpriteRenderer2D* m_SpriteRenderer;
	Engine::AnimatorComponent* m_Animator;
 	Engine::Rigidbody2D* m_RigidBody2d;
 	Engine::BoxCollider2DComponent* m_Collider;

	float m_FireRate = 0.2f;
	float m_NexShotTime = 0.0f;
	float m_CurrentTime = 0.0f;

	float lastX = -2;

	MissileTier m_MissileTier;

};

