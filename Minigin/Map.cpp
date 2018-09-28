#include "MiniginPCH.h"
#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS\ECS.h"
#include "ECS\Components.h"

//extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : m_TextId(tID), m_MapScale(ms), m_TileSize(ts)
{
	m_ScaledSize = ms * ts;
	//AssetManager* pAssets = new AssetManager(&m_Manager);
}

Map::~Map()
{
}

void Map::LoadMap(const std::string& path, int sizeX, int sizeY,Manager& manager)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * m_TileSize;
			mapFile.get(c);
			srcX = atoi(&c) * m_TileSize;
			AddTile(srcX, srcY, x * m_ScaledSize, y * m_ScaledSize,manager);
			
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * m_ScaledSize, y * m_ScaledSize, m_ScaledSize);
				tcol.addComponent<SpriteComponent>();
				tcol.addGroup(Game::groupColliders);
				
			}
			else if(c == '2')
			{
				AddPellet(x * m_ScaledSize, y * m_ScaledSize);
				
			}
			else if (c == '3')
			{
				AddPowerPellet(x * m_ScaledSize, y * m_ScaledSize);

			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos,Manager& manager)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, m_TileSize, m_MapScale, m_TextId);

	tile.addGroup(Game::groupMap);
	
}

void Map::AddPellet( int xpos, int ypos)
{
	Game::m_sEntityAssembler->CreatePellet(Vector2D(float(xpos), float(ypos)), "pellet");
}

void  Map::AddPowerPellet(int xpos, int ypos)
{
	Game::m_sEntityAssembler->CreatePowerPellet(Vector2D(float(xpos), float(ypos)), "powerpellet");
}