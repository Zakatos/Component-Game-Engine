#include "MiniginPCH.h"
#include "RendererComponent.h"

SDL_Texture* RendererComponent::LoadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::m_sRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}


void RendererComponent::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::m_sRenderer, tex, &src, &dest, NULL, NULL, flip);
}

