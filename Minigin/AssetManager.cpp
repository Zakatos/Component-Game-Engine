#include "MiniginPCH.h"
#include "AssetManager.h"
#include "ECS\Components.h"

AssetManager::AssetManager(Manager* man) : m_pManager(man)
{}

AssetManager::~AssetManager()
{
	m_Fonts.clear();
	m_Textures.clear();
}



void AssetManager::AddTexture(std::string id, const char* path)
{
	m_Textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return m_Textures[id];
}

void AssetManager::AddFont(const std::string& id, const std::string& path, int fontSize)
{
	m_Fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(const std::string& id)
{
	return m_Fonts[id];
}


