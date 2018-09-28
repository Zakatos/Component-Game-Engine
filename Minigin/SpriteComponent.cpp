#include "MiniginPCH.h"
#include "ECS/SpriteComponent.h"
#include "RendererComponent.h"

SpriteComponent::SpriteComponent(std::string id)
{
	setTex(id);
}

SpriteComponent::SpriteComponent(std::string id, bool isAnimated)
{
	m_IsAnimated = isAnimated;

	//Animation idle = Animation(0, 3, 100);
	//Animation walk = Animation(1, 8, 100);

	/*m_Animations.emplace("Idle", idle);
	m_Animations.emplace("Walk", walk);*/

	//Play("Idle");

	setTex(id);
}


SpriteComponent::~SpriteComponent()
{
	//std::map<const char*, Animation>::iterator itr = m_Animations.begin(); itr != m_Animations.end(); itr++;
	//if (itr != m_Animations.end())
	//{
	//	// found it - delete it
	//	delete itr->first;
	//	m_Animations.erase(itr);
	//}
}

void SpriteComponent::setTex(std::string id)
{
	m_pTexture = Game::m_sAssets->GetTexture(id);
}



void SpriteComponent::init()
{
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
	m_pRenderer = &m_pEntity->getComponent<RendererComponent>();

	m_SrcRect.x = m_SrcRect.y = 0;
	m_SrcRect.w = m_pTransform->GetWidth();
	m_SrcRect.h = m_pTransform->GetHeight();
}


void SpriteComponent::update()
{
	if (m_IsAnimated)
	{
		m_SrcRect.x = m_SrcRect.w * static_cast<int>((SDL_GetTicks() / m_Speed) % m_Frames);
	}

	m_SrcRect.y = m_AnimIndex * m_pTransform->GetHeight();

	m_DestRect.x = static_cast<int>(m_pTransform->GetPosition().m_X);
	m_DestRect.y = static_cast<int>(m_pTransform->GetPosition().m_Y);
	m_DestRect.w = m_pTransform->GetWidth() * m_pTransform->GetScale();
	m_DestRect.h = m_pTransform->GetWidth() * m_pTransform->GetScale();
}


void SpriteComponent::draw()
{
	m_pRenderer->Draw(m_pTexture, m_SrcRect, m_DestRect, spriteFlip);
}

//void SpriteComponent::Play(const char* animName)
//{
//	//m_Frames = m_Animations[animName].m_Frames;
//	//m_AnimIndex = m_Animations[animName].m_Index;
//	//m_Speed = m_Animations[animName].m_Speed;
//}




