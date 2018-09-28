#include "MiniginPCH.h"
#include "ECS/UILabel.h"


UILabel::UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) : m_LabelText(text), m_LabelFont(font), m_TextColour(colour)
{
	m_Position.x = xpos;
	m_Position.y = ypos;

	SetLabelText(m_LabelText, m_LabelFont);
}

UILabel::~UILabel()
{
	SDL_DestroyTexture(m_pLabelTexture);
}

//void UILabel::update()
//{
//	if (m_NeedsUpdate)
//	{
//				SDL_Surface* pSurf = TTF_RenderText_Blended(Game::m_sAssets->GetFont(m_LabelFont), m_LabelText.c_str(), m_TextColour);
//		
//				if (pSurf == nullptr)
//					throw std::runtime_error("Could not create SDL Surface: " + std::string(SDL_GetError()));
//		
//				SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::Renderer, pSurf);
//		
//				if (pTexture == nullptr)
//					throw std::runtime_error("Could not create SDL Texture: " + std::string(SDL_GetError()));
//		
//				SDL_FreeSurface(pSurf);
//		
//				SDL_DestroyTexture(m_pLabelTexture);
//
//				m_pLabelTexture = SDL_CreateTextureFromSurface(Game::Renderer, pSurf);
//				m_NeedsUpdate = false;
//			}
//}


void UILabel::SetLabelText(std::string text, std::string font)
{
	
		SDL_Surface* surf = TTF_RenderText_Blended(Game::m_sAssets->GetFont(font), text.c_str(), m_TextColour);
		m_pLabelTexture = SDL_CreateTextureFromSurface(Game::m_sRenderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(m_pLabelTexture, nullptr, nullptr, &m_Position.w, &m_Position.h);
		m_NeedsUpdate = true;
	
}

void UILabel::draw()
{
	SDL_RenderCopy(Game::m_sRenderer, m_pLabelTexture, nullptr, &m_Position);
}

