#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "ECS/ECS.h"
#include <chrono>
#include "EntityAssembler.h"

class AssetManager;
class ColliderComponent;
class EntityAssembler;
class Map;

class Game
{
public:
	enum GameScene : std::size_t
	{
		menu,
		singleplayer,
		twoplayerghost,
		twoplayerpacman,
		exit
	};
	
	Game();
	~Game();
	void init(const char* title, int width, int height, bool fullscreen);
	//void handleEvents();
	void update();
	const bool& running() const { return m_sIsRunning; }
	void render();
	void clean();
	static SDL_Renderer *m_sRenderer;
	static SDL_Event m_sEvent;
	static bool m_sIsRunning;
	static std::unique_ptr<AssetManager> m_sAssets;
	static std::unique_ptr<EntityAssembler> m_sEntityAssembler;
	static Manager m_sManager;
	static int m_GameSceneNum;
	static float m_sElapsedsec;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupGhosts,
		groupColliders,
		groupProjectiles,
		groupPellets,
		groupPowerPellets
	};
	
	Game(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) = delete;
private:
	//Methods

	void CountFPS();
	void SetUpTextures();
	void SetUpPlayers();
	void SetUpGhosts();
	void ResetGhosts();
	void SetUpMenu();
	void SetGameScene();
	void SetUpVersusScene();
	void SetUpCoopScene();
	void DeleteGhosts();
	void CheckScene();
	void CheckGameConditions();
	//Member Variables

	//Entities
	Entity& m_Pacman;
	Entity& m_GreenGhost;
	Entity& m_BlueGhost;
	Entity& m_PinkGhost;
	Entity& m_RedGhost;
	Entity& m_FpsLabel;
	Entity& m_GameStateLabel;
	Entity& m_MainMenu;
	Entity& m_Cursor;
	Entity& m_LivesLabel;
	Entity& m_MsPacman;
	Entity& m_PlayerGhost;
	Entity& m_GameInfo;
	//Entity Groups
	std::vector<Entity*>& m_pTiles;
	std::vector<Entity*>& m_pPlayers;
	std::vector<Entity*>& m_pPellets;
	std::vector<Entity*>& m_pPowerPellets;
	std::vector<Entity*>& m_pGhosts;
	std::vector<Entity*>& m_pColliders;
	//Game Variables
	float m_TotalTime;
	float m_ElapsedTime;
	int m_FPS;
	float m_FPSTimer;
	int m_FPSCount;
	float m_MaxElapsedTime = 0.1f;
	std::chrono::high_resolution_clock::time_point m_GameTime;
	float m_FrameTime;
	int m_Cnt = 0;
	SDL_Window *m_pWindow;
	int m_NumberOfPellets;
	std::stringstream m_FpsStream;
	std::stringstream m_WinStream;	
	GameScene m_GameScene = GameScene::menu;
	
	//Pacman Variables
	int m_Lives = 3;
	//scenes
	bool m_VersusIsSelected = false;
	bool m_CoopIsSelected = false;
	bool m_IsSceneSelected = false;
	bool m_IsSinglePlayerSelected = false;

	//Level variables
	std::unique_ptr<Map> m_upMap;

};