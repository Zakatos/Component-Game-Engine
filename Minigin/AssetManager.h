#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
	void AddFont(const std::string& id, const std::string& path, int fontSize);
	TTF_Font* GetFont(const std::string& id);
	AssetManager(const AssetManager& other) = delete;
	AssetManager(AssetManager&& other) = delete;
	AssetManager& operator=(const AssetManager& other) = delete;
	AssetManager& operator=(AssetManager&& other) = delete;
private:

	Manager* m_pManager;
	std::map<std::string, SDL_Texture*> m_Textures;
	std::map<std::string, TTF_Font*> m_Fonts;
};