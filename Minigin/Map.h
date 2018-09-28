#pragma once
#include <string>
#include "TextureManager.h"


class Manager;

class Map 
{
public:
	 
	Map(std::string tID, int ms, int ts);
	~Map();

	void LoadMap(const std::string& path, int sizeX, int sizeY,Manager& manager);
	void AddTile(int srcX, int srcY, int xpos, int ypos,Manager& manager);
	void AddPellet( int xpos, int ypos);
	void AddPowerPellet(int xpos, int ypos);
	
	
private:
	std::string m_TextId;
	int m_MapScale;
	int m_TileSize;
	int m_ScaledSize;
	
};
