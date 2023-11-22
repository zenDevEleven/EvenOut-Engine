#include "Background.h"

void Background::Start()
{
	LOG_APP("Loading background texture", Engine::LOG_INFO);
	m_SpriteRenderer = AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/galaxy2.bmp");
}

void Background::Update(float deltaTime)
{
}

