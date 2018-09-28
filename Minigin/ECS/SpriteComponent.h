#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"


class TransformComponent;
class RendererComponent;

class SpriteComponent final : public Component
{
private:
	TransformComponent * m_pTransform;
	RendererComponent * m_pRenderer;
	SDL_Texture *m_pTexture;
	SDL_Rect m_SrcRect, m_DestRect;

	bool m_IsAnimated = false;
	int m_Frames = 0;
	int m_Speed = 100;

public:

	int m_AnimIndex = 0;
	//std::map<const char*, Animation> m_Animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	SpriteComponent() = default;
	SpriteComponent(std::string id);
	SpriteComponent(std::string id, bool isAnimated);	
	~SpriteComponent();
	void setTex(std::string id);
	void init() override;
	void update() override;
	void draw();
	//void Play(const char* animName);
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) = delete;

};