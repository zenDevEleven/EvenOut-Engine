#include "ParallaxBG.h"
#include "Global.h"

void ParallaxBG::Start()
{
	__super::Start();

	m_Transform = &AddComponent<Engine::TransformComponent>();

	m_SpriteRenderers.push_back(&AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/rocksBg.bmp", glm::vec2(640, 1780), 0));
	m_SpriteRenderers.push_back(&AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/rocks.bmp", glm::vec2(640, 1780), 0));

	m_Transform->SetPosition(0.0f, -m_SpriteRenderers[m_SpriteRendererIndex]->m_SpriteTexture.t_TextHeight);

}

void ParallaxBG::Update(float deltaTime)
{
	__super::Update(deltaTime);

	
	if (m_Transform->Position.y >= Global::WIDTH)	{
		m_SpriteRendererIndex++;
		if (m_SpriteRendererIndex >= m_SpriteRenderers.size())
			m_SpriteRendererIndex = 0;

		m_Transform->SetPosition(0.0f, -m_SpriteRenderers[m_SpriteRendererIndex]->m_SpriteTexture.t_TextHeight);
	}
	else
	{
		m_Transform->AddPos(0, m_ScollingSpeed  * deltaTime);
	}
}

void ParallaxBG::OnContactEvent(Object* other)
{
	
}

void ParallaxBG::OnEndContactEvent(Object* other)
{
	
}
