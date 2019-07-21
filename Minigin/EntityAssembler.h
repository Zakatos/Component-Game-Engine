#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"
#include "SDL_ttf.h"

class EntityAssembler
{
public:
	EntityAssembler(Manager* man);
	~EntityAssembler();

	//gameobjects
	void CreatePacMan(Vector2D pos, const std::string& id);
	void CreatePellet(Vector2D pos, const std::string& id);
	void CreatePowerPellet(Vector2D pos, const std::string& id);
	EntityAssembler(const EntityAssembler& other) = delete;
	EntityAssembler(EntityAssembler&& other) = delete;
	EntityAssembler& operator=(const EntityAssembler& other) = delete;
	EntityAssembler& operator=(EntityAssembler&& other) = delete;
private:

	Manager* m_pManager = nullptr;
};
