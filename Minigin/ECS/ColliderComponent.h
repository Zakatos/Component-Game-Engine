#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"
#include "../TextureManager.h"


class TransformComponent;
class RendererComponent;

class ColliderComponent final : public Component
{
public:
	ColliderComponent(const std::string& t);
	ColliderComponent(const std::string& t, int xpos, int ypos, int size);
	~ColliderComponent();
	const SDL_Rect& GetCollider() const { return  m_Collider; }
	void init() override;		
	void update() override;
	void draw() ;
	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) = delete;
private:
	SDL_Rect m_Collider{};
	std::string m_Tag;
	SDL_Texture* m_pTex = nullptr;
	SDL_Rect m_SrcR, m_destR;
	TransformComponent* m_pTransform = nullptr;
	RendererComponent* m_pRenderer = nullptr;

};