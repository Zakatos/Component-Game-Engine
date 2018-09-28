#pragma once
#include "ECS/Components.h"
#include "Game.h"

class RendererComponent final : public Component
{

public:
	 SDL_Texture* LoadTexture(const char* texture);
	 void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

