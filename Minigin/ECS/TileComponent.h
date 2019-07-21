#pragma once

#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"
#include "../TextureManager.h"


class AssetManager;
class RendererComponent;

class TileComponent final : public Component
{
public:
	
	
	
	TileComponent() = default;
	~TileComponent();
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale,const std::string& id);
	void init() override;
	void update() override;
	void draw() ;
	TileComponent(const TileComponent& other) = delete;
	TileComponent(TileComponent&& other) = delete;
	TileComponent& operator=(const TileComponent& other) = delete;
	TileComponent& operator=(TileComponent&& other) = delete;


private:
	SDL_Texture * m_pTexture = nullptr;
	SDL_Rect m_SrcRect, m_DestRect;
	Vector2D m_Position;
	RendererComponent* m_pRenderer = nullptr;
};