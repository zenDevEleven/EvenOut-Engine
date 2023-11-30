#include "Background.h"

void Background::Start()
{
	LOG_APP("Loading background texture", Engine::LOG_INFO);
	m_SpriteRenderer = AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/galaxy2.bmp", 0);
}

void Background::Update(float deltaTime)
{
}

void Background::OnContactEvent(Object* other)
{
}

void Background::OnEndContactEvent(Object* other)
{
	
}

