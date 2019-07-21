#include "MiniginPCH.h"
#include "ECS/TileComponent.h"
#include "AssetManager.h"
#include "RendererComponent.h"

TileComponent::TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale,const std::string& id)
{
	m_pTexture = Game::m_sAssets->GetTexture(id);

	m_SrcRect.x = srcX;
	m_SrcRect.y = srcY;
	m_SrcRect.w = m_SrcRect.h = tsize;
	m_Position.m_X = static_cast<float>(xpos);
	m_Position.m_Y = static_cast<float>(ypos);
	m_DestRect.w = m_DestRect.h = tsize * tscale;
}


TileComponent::~TileComponent()
{
	SDL_DestroyTexture(m_pTexture);
	//delete m_pRenderer;
	//m_pRenderer = nullptr;
}


void TileComponent::init()
{
	m_pRenderer = &m_pEntity->getComponent<RendererComponent>();
}

void TileComponent::update()
{
	m_DestRect.x = static_cast<int>(m_Position.m_X);
	m_DestRect.y = static_cast<int>(m_Position.m_Y);
}


void TileComponent::draw()
{
	m_pRenderer->Draw(m_pTexture, m_SrcRect, m_DestRect, SDL_FLIP_NONE);
}



