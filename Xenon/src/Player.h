#pragma once
#include "Engine/Core/Actor.h"
#include "Engine/Core/Components.h"

class Player : public Engine::Actor
{
public:
	Player();
	~Player() {}
	void Start() override;
	void Update(float deltaTime) override;
private:
	Engine::TransformComponent m_Transform;
	Engine::SpriteRenderer2D m_SpriteRenderer;
	Engine::AnimatorComponent m_Animator;

};

