#pragma once
#include "Engine/Core/Actor.h"
#include "Engine/Core/Components.h"

class Missile : public Engine::Actor
{
public:
	Missile(float missileSpeed, glm::vec2 spawnPos);
	virtual ~Missile() {};

	void Start() override;
	void Update(float deltaTime) override;
private:
	Engine::TransformComponent* m_Transform;
	Engine::SpriteRenderer2D* m_SpriteRenderer;
	Engine::AnimatorComponent* m_Animator;

	float m_MissileSpeed;

};

