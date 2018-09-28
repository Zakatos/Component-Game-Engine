#include "MiniginPCH.h"
#include "EntityAssembler.h"
#include "ECS\Components.h"


EntityAssembler::EntityAssembler(Manager* man) : m_pManager(man)
{
}


EntityAssembler::~EntityAssembler()
{
	
}

void EntityAssembler::CreatePacMan(Vector2D pos, std::string id)
{
	auto& pacMan(m_pManager->addEntity());
	pacMan.addComponent<TransformComponent>(pos.m_X, pos.m_Y, 32, 32, 1);
	pacMan.addComponent<SpriteComponent>(id, false);
	pacMan.addComponent<ColliderComponent>("pacman");
	pacMan.addComponent<PlayerController>();
	pacMan.addGroup(Game::groupPlayers);
}

void EntityAssembler::CreatePellet(Vector2D pos, std::string id)
{
	const float pelletOffset = 10.f;
	auto& pellet(m_pManager->addEntity());
	Game::m_sAssets->AddTexture("pellet", "Assets/terrain_ss.png");
	//AddTexture("pellet", "Assets/terrain_ss.png");
	pellet.addComponent<TransformComponent>(pos.m_X + pelletOffset, pos.m_Y + pelletOffset, 12, 12, 1);
	pellet.addComponent<SpriteComponent>(id, false);
	pellet.addComponent<ColliderComponent>("pellet");
	pellet.addGroup(Game::groupPellets);
}

void EntityAssembler::CreatePowerPellet(Vector2D pos, std::string id)
{
	const float pelletOffset = 10.f;
	auto& powerpellet(m_pManager->addEntity());
	Game::m_sAssets->AddTexture("powerpellet", "Assets/SmallPowerPellet.png");
	//AddTexture("powerpellet", "Assets/SmallPowerPellet.png");
	powerpellet.addComponent<TransformComponent>(pos.m_X + pelletOffset, pos.m_Y + pelletOffset, 12, 12, 1);
	powerpellet.addComponent<SpriteComponent>(id, false);
	powerpellet.addComponent<ColliderComponent>("powerpellet");
	powerpellet.addGroup(Game::groupPowerPellets);
}
