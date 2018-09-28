#include "MiniginPCH.h"
#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>
#include <iomanip>
#include "ECS/UILabel.h"
#include <chrono>
#include "AiComponent.h"
#include "ctime"
#include "PlayerPhysicsComponent.h"
#include "GhostPhysicsComponent.h"
#include "CursorComponent.h"
#include "GhostPlayerController.h"
#include "RendererComponent.h"
#include "ThreadComponent.h"


Manager Game::m_sManager;
SDL_Renderer* Game::m_sRenderer = nullptr;
std::unique_ptr<EntityAssembler> Game::m_sEntityAssembler(new EntityAssembler(&m_sManager));
SDL_Event Game::m_sEvent;
std::unique_ptr<AssetManager> Game::m_sAssets(new AssetManager(&m_sManager));
bool Game::m_sIsRunning = false;
int Game::m_GameSceneNum =0;
float Game::m_sElapsedsec = 0;

Game::Game()
	:m_Pacman(m_sManager.addEntity()), m_GreenGhost(m_sManager.addEntity()),
m_BlueGhost(m_sManager.addEntity()),m_PinkGhost(m_sManager.addEntity()),
m_RedGhost(m_sManager.addEntity()),m_FpsLabel(m_sManager.addEntity()),
m_GameStateLabel(m_sManager.addEntity()),m_pTiles(m_sManager.getGroup(Game::groupMap)),
m_pPlayers(m_sManager.getGroup(Game::groupPlayers)),m_pGhosts(m_sManager.getGroup(Game::groupGhosts)),
m_pColliders(m_sManager.getGroup(Game::groupColliders)),m_pPowerPellets(m_sManager.getGroup(Game::groupPowerPellets)),
m_pPellets(m_sManager.getGroup(Game::groupPellets)),m_MainMenu(m_sManager.addEntity()),m_LivesLabel(m_sManager.addEntity()),
m_Cursor(m_sManager.addEntity()),m_PlayerGhost(m_sManager.addEntity()),m_MsPacman(m_sManager.addEntity()),
m_GameInfo(m_sManager.addEntity())
{	
}

Game::~Game()
{
	
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	srand(unsigned int((NULL)));
	
	m_GameTime = std::chrono::high_resolution_clock::now();
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		m_sRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		if (m_sRenderer)
		{
			SDL_SetRenderDrawColor(m_sRenderer, 255, 255, 255, 255);
		}

		m_sIsRunning = true;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}
	//Set up Textures and Fonts
	SetUpTextures();
	//Map Initialization
	m_upMap = std::make_unique<Map>("terrain", 1, 32);
	m_upMap->LoadMap("Assets/map.map", 25, 20,m_sManager);

	SDL_Color white = { 255, 255, 255, 255 };

	//Ghost And Player SetUp
	SetUpPlayers();	
	SetUpMenu();
	
	m_Lives = m_Pacman.getComponent<PlayerController>().GetLives();
	m_NumberOfPellets = int(m_pPellets.size()) + int(m_pPowerPellets.size());
	//Set Labels
	m_FpsLabel.addComponent<UILabel>(10, 10, "Test String", "arial", white);
	m_FpsLabel.getComponent<UILabel>().SetLabelText(std::to_string(m_FPS), "arial");
	m_GameStateLabel.addComponent<UILabel>(360, 370, "", "arial", white);
	m_LivesLabel.addComponent<UILabel>(5, 620, "Test String", "arial", white);
	m_LivesLabel.getComponent<UILabel>().SetLabelText("Lives: " + std::to_string( m_Pacman.getComponent<PlayerController>().GetLives()), "arial");
	m_GameInfo.addComponent<UILabel>(200, 500, "Use 1,2,3 to choose and press enter to select mode", "arial", white);
}


void Game::update()
{
	if(!m_IsSceneSelected)
	{
		CheckScene();
	}
	switch (m_GameScene)
	{
	case GameScene::menu:

		m_sManager.refresh();
		m_MainMenu.update();
		m_Cursor.update();
		m_GameInfo.update();
		break;
	case GameScene::singleplayer:
		
		m_sManager.refresh();
		m_sManager.update();
		CountFPS();
		
		m_Pacman.getComponent<PlayerController>().CheckPelletsCollisions(m_pPellets, m_pPowerPellets, m_NumberOfPellets);
		for (auto& p : m_pGhosts)
		{
			p->getComponent<AiComponent>().CheckPlayerCollision(m_pPlayers);
		}
		
		m_FpsLabel.getComponent<UILabel>().SetLabelText(std::to_string(m_FPS), "arial");
		m_LivesLabel.getComponent<UILabel>().SetLabelText("Lives : "+std::to_string(m_Pacman.getComponent<PlayerController>().GetLives()), "arial");
				
		CheckGameConditions();
				
		break;
	case GameScene::twoplayerghost:

		m_sManager.refresh();
		m_sManager.update();		
		CountFPS();	
		m_Pacman.getComponent<PlayerController>().CheckPelletsCollisions(m_pPellets, m_pPowerPellets, m_NumberOfPellets);
		m_PlayerGhost.getComponent<GhostPlayerController>().CheckPlayerCollision(m_pPlayers);					
		m_FpsLabel.getComponent<UILabel>().SetLabelText(std::to_string(m_FPS), "arial");
		m_LivesLabel.getComponent<UILabel>().SetLabelText("Lives : " + std::to_string(m_Pacman.getComponent<PlayerController>().GetLives()), "arial");
		CheckGameConditions();
		
		break;
	
	case GameScene::twoplayerpacman:
			
		
		m_sManager.refresh();
		m_sManager.update();
		CountFPS();		
		m_Pacman.getComponent<PlayerController>().CheckPelletsCollisions(m_pPellets, m_pPowerPellets, m_NumberOfPellets);
		m_MsPacman.getComponent<PlayerController>().CheckPelletsCollisions(m_pPellets, m_pPowerPellets, m_NumberOfPellets);
		
		for (auto& p : m_pGhosts)
		{
			p->getComponent<AiComponent>().CheckPlayerCollision(m_pPlayers);
		}					
		m_FpsLabel.getComponent<UILabel>().SetLabelText(std::to_string(m_FPS), "arial");
		m_LivesLabel.getComponent<UILabel>().SetLabelText("Lives : " + std::to_string(m_Pacman.getComponent<PlayerController>().GetLives()), "arial");		
		CheckGameConditions();

		break;
	case GameScene::exit:
		m_sIsRunning = false;
		break;
	}
}
void Game::render()
{
	
	switch (m_GameScene)
	{
	case GameScene::menu:
		SDL_RenderClear(m_sRenderer);
		m_MainMenu.getComponent<SpriteComponent>().draw();
		m_Cursor.getComponent<SpriteComponent>().draw();
		m_GameInfo.getComponent<UILabel>().draw();
		SetGameScene();
		SDL_RenderPresent(m_sRenderer);
		break;
	
	case GameScene::singleplayer:
		SDL_RenderClear(m_sRenderer);
		for (auto& t : m_pTiles)
		{
			t->getComponent<TileComponent>().draw();
		}
		for (auto& c : m_pColliders)
		{
			c->getComponent<ColliderComponent>().draw();
		}
		m_FpsLabel.getComponent<UILabel>().draw();
		m_GameStateLabel.getComponent<UILabel>().draw();
		m_LivesLabel.getComponent<UILabel>().draw();
		for (auto& p : m_pPellets)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		for (auto& p : m_pPowerPellets)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		for (auto& g : m_pGhosts)
		{
			g->getComponent<SpriteComponent>().draw();
		}
		for (auto& p : m_pPlayers)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		SDL_RenderPresent(m_sRenderer);
		break;
	
	case twoplayerghost:
		SDL_RenderClear(m_sRenderer);
		for (auto& t : m_pTiles)
		{
			t->getComponent<TileComponent>().draw();
		}

		for (auto& c : m_pColliders)
		{
			c->getComponent<ColliderComponent>().draw();
		}

		m_FpsLabel.getComponent<UILabel>().draw();
		m_GameStateLabel.getComponent<UILabel>().draw();
		m_LivesLabel.getComponent<UILabel>().draw();
		for (auto& p : m_pPellets)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		for (auto& p : m_pPowerPellets)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		
		for (auto& p : m_pPlayers)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		for (auto& g : m_pGhosts)
		{
			g->getComponent<SpriteComponent>().draw();
		}
		SDL_RenderPresent(m_sRenderer);
		break;
	
	case twoplayerpacman:
		SDL_RenderClear(m_sRenderer);
		for (auto& t : m_pTiles)
		{
			t->getComponent<TileComponent>().draw();
		}
		for (auto& c : m_pColliders)
		{
			c->getComponent<ColliderComponent>().draw();
		}
		m_FpsLabel.getComponent<UILabel>().draw();
		m_GameStateLabel.getComponent<UILabel>().draw();
		for (auto& p : m_pPellets)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		for (auto& p : m_pPowerPellets)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		for (auto& g : m_pGhosts)
		{
			g->getComponent<SpriteComponent>().draw();
		}
		for (auto& p : m_pPlayers)
		{
			p->getComponent<SpriteComponent>().draw();
		}
		SDL_RenderPresent(m_sRenderer);
		break;
	case GameScene::exit:
		m_sIsRunning = false;

			break;
	}
}

void Game::clean()
{
	m_Pacman.getComponent<InputComponent>().~InputComponent();
	for(auto& p : m_pPlayers)
	{
		p->destroy();
	}
	m_pPlayers.clear();
	for (auto& p : m_pTiles)
	{
		p->destroy();
	}
	m_pTiles.clear();
	for (auto& p : m_pPellets)
	{
		p->destroy();
	}
	m_pPellets.clear();
	for (auto& p : m_pPowerPellets)
	{
		p->destroy();
	}
	m_pPowerPellets.clear();
	
	for (auto& p : m_pGhosts)
	{
		p->destroy();
	}
	m_pGhosts.clear();
	for (auto& p : m_pColliders)
	{
		p->destroy();
	}
	
	m_pColliders.clear();
	m_FpsLabel.destroy();
	m_GameInfo.destroy();
	m_LivesLabel.destroy();
	
	InputManager::GetInstance().Clear();
	m_sManager.refresh();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_sRenderer);
	SDL_Quit();
}

void Game::CountFPS()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(now - m_GameTime);

	m_sElapsedsec = timeSpan.count();
	
	if (m_sElapsedsec > m_MaxElapsedTime)
	{
		m_sElapsedsec = m_MaxElapsedTime;
	}
	
	m_TotalTime += m_sElapsedsec;
	m_GameTime = now;

	//FPS
	m_FPSTimer += m_sElapsedsec;
	++m_FPSCount;

	if (m_FPSTimer >= 1.0f) {
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
		m_FPSTimer -= 1.0f;
	}
}

void Game::SetUpTextures()
{
	m_sAssets->AddFont("arial", "Assets/arial.ttf", 16);
	m_sAssets->AddTexture("terrain", "Assets/terrain_ss.png");
	m_sAssets->AddTexture("player", "Assets/m_Pacman.png");
	m_sAssets->AddTexture("player2", "Assets/MissPacMan.png");
	m_sAssets->AddTexture("projectile", "Assets/proj.png");
	m_sAssets->AddTexture("m_Pacman", "Assets/PacmanSmall.png");
	m_sAssets->AddTexture("m_GreenGhost", "Assets/GreenGhost.png");
	m_sAssets->AddTexture("m_RedGhost", "Assets/redGhost.png");
	m_sAssets->AddTexture("m_BlueGhost", "Assets/BlueGhost.png");
	m_sAssets->AddTexture("m_PinkGhost", "Assets/PinkGhost.png");
	m_sAssets->AddTexture("ScaredGhost", "Assets/ScaredGhost.png");
	m_sAssets->AddTexture("Cherry", "Assets/Cherry.png");
	m_sAssets->AddTexture("MainMenu", "Assets/MainMenu.png");
	m_sAssets->AddTexture("MsPacman", "Assets/MissPacMan.png");
}

void Game::SetUpPlayers()
{
	m_Pacman.addComponent<TransformComponent>(400.0f, 455.0f, 20, 20, 1);
	m_Pacman.addComponent<SpriteComponent>("m_Pacman", false);	
	m_Pacman.addComponent<ColliderComponent>("m_Pacman");
	m_Pacman.addGroup(groupPlayers);
	m_Pacman.addComponent<PlayerPhysicsComponent>();
	m_Pacman.getComponent<PlayerPhysicsComponent>().GetCollisionInformation(m_pColliders);
	m_Pacman.addComponent<PlayerController>();
	m_Pacman.addComponent<InputComponent>(ControllerButton::DpadLeft, ControllerButton::DpadUp, ControllerButton::DpadRight, ControllerButton::DpadDown);
	
	
}

void Game::SetUpGhosts()
{
	m_GreenGhost.addComponent<TransformComponent>(390.f, 320.f, 20, 20, 1);
	m_GreenGhost.addComponent<SpriteComponent>("m_GreenGhost", false);
	m_GreenGhost.addComponent<ColliderComponent>("ghost");
	m_GreenGhost.addGroup(groupGhosts);
	m_GreenGhost.addComponent<GhostPhysicsComponent>();
	m_GreenGhost.getComponent<GhostPhysicsComponent>().GetCollisionInformation(m_pColliders);
	m_GreenGhost.addComponent<AiComponent>();
	m_GreenGhost.getComponent<AiComponent>().SetState(State::Wandering);
	m_GreenGhost.getComponent<AiComponent>().setSpriteName("m_GreenGhost");
	m_GreenGhost.addComponent<ThreadComponent>();

	m_BlueGhost.addComponent<TransformComponent>(390.f, 320.f, 20, 20, 1);
	m_BlueGhost.addComponent<SpriteComponent>("m_BlueGhost", false);
	m_BlueGhost.addComponent<ColliderComponent>("m_BlueGhost");
	m_BlueGhost.addGroup(groupGhosts);	
	m_BlueGhost.addComponent<GhostPhysicsComponent>();
	m_BlueGhost.getComponent<GhostPhysicsComponent>().GetCollisionInformation(m_pColliders);
	m_BlueGhost.addComponent<AiComponent>();
	m_BlueGhost.getComponent<AiComponent>().SetState(State::Wandering);
	m_BlueGhost.getComponent<AiComponent>().setSpriteName("m_BlueGhost");
	m_BlueGhost.addComponent<ThreadComponent>();

	m_PinkGhost.addComponent<TransformComponent>(390.f, 320.f, 20, 20, 1);
	m_PinkGhost.addComponent<SpriteComponent>("m_PinkGhost", false);
	m_PinkGhost.addComponent<ColliderComponent>("m_PinkGhost");
	m_PinkGhost.addGroup(groupGhosts);
	m_PinkGhost.addComponent<GhostPhysicsComponent>();
	m_PinkGhost.getComponent<GhostPhysicsComponent>().GetCollisionInformation(m_pColliders);
	m_PinkGhost.addComponent<AiComponent>();
	m_PinkGhost.getComponent<AiComponent>().SetState(State::Wandering);
	m_PinkGhost.getComponent<AiComponent>().setSpriteName("m_PinkGhost");
	m_PinkGhost.addComponent<ThreadComponent>();

	m_RedGhost.addComponent<TransformComponent>(390.f, 320.f, 20, 20, 1);
	m_RedGhost.addComponent<SpriteComponent>("m_RedGhost", false);
	m_RedGhost.addComponent<ColliderComponent>("m_RedGhost");	
	m_RedGhost.addGroup(groupGhosts);
	m_RedGhost.addComponent<GhostPhysicsComponent>();
	m_RedGhost.getComponent<GhostPhysicsComponent>().GetCollisionInformation(m_pColliders);
	m_RedGhost.addComponent<AiComponent>();
	m_RedGhost.getComponent<AiComponent>().SetState(State::Wandering);
	m_RedGhost.getComponent<AiComponent>().setSpriteName("m_RedGhost");
	m_RedGhost.addComponent<ThreadComponent>();

}

void Game::ResetGhosts()
{
	m_GreenGhost.getComponent<TransformComponent>().Translate(390.f, 320.f);
	m_BlueGhost.getComponent<TransformComponent>().Translate(390.f, 320.f);
	m_PinkGhost.getComponent<TransformComponent>().Translate(390.f, 320.f);
	m_RedGhost.getComponent<TransformComponent>().Translate(390.f, 320.f);
}


void Game::SetUpMenu()
{
	m_MainMenu.addComponent<TransformComponent>(0.f, 0.f,800,640, 1);
	m_MainMenu.addComponent<SpriteComponent>("MainMenu", false);
	m_Cursor.addComponent<TransformComponent>(295.f, 400.f,12,12,1);
	m_Cursor.addComponent<SpriteComponent>("m_Pacman", false);
	m_Cursor.addComponent<CursorComponent>();
}
void Game::SetUpVersusScene()
{
	m_PlayerGhost.addComponent<TransformComponent>(390.f, 320.f, 20, 20, 1);
	m_PlayerGhost.addComponent<SpriteComponent>("m_RedGhost", false);
	m_PlayerGhost.addComponent<ColliderComponent>("GhostPlayer");
	m_PlayerGhost.addGroup(groupGhosts);
	m_PlayerGhost.addComponent<GhostPhysicsComponent>().GetCollisionInformation(m_pColliders);
	m_PlayerGhost.addComponent<GhostPlayerController>();
	m_PlayerGhost.getComponent<GhostPlayerController>().setSpriteName("m_RedGhost");
	m_PlayerGhost.addComponent<InputComponent>(ControllerButton::A, ControllerButton::W, ControllerButton::D, ControllerButton::S);
}
void Game::SetUpCoopScene()
{
	m_MsPacman.addComponent<TransformComponent>(450.0f, 450.0f, 20, 20, 1);
	m_MsPacman.addComponent<SpriteComponent>("MsPacman", false);
	m_MsPacman.addComponent<ColliderComponent>("MsPacman");
	m_MsPacman.addGroup(groupPlayers);
	m_MsPacman.addComponent<PlayerPhysicsComponent>();
	m_MsPacman.getComponent<PlayerPhysicsComponent>().GetCollisionInformation(m_pColliders);
	m_MsPacman.addComponent<PlayerController>();
	m_MsPacman.addComponent<InputComponent>(ControllerButton::A, ControllerButton::W, ControllerButton::D, ControllerButton::S);
}


void Game::SetGameScene()
{
	m_GameScene = GameScene(m_GameSceneNum);
}

void Game::DeleteGhosts()
{
	m_RedGhost.destroy();
	m_BlueGhost.destroy();
	m_PinkGhost.destroy();
	m_GreenGhost.destroy();
}

void Game::CheckScene()
{
	if(!m_IsSceneSelected)
	{
		if (m_GameSceneNum == 1 && !m_IsSinglePlayerSelected)
		{
			SetUpGhosts();
			m_IsSinglePlayerSelected = true;
			m_IsSceneSelected = true;
		}
		
		if (m_GameSceneNum == 2 && !m_VersusIsSelected)
		{
			SetUpVersusScene();
			m_VersusIsSelected = true;
			m_IsSceneSelected = true;
		}
		if (m_GameSceneNum == 3 && !m_CoopIsSelected)
		{
			SetUpGhosts();
			SetUpCoopScene();
			m_CoopIsSelected = true;
			m_IsSceneSelected = true;
		}
	}
}

void  Game::CheckGameConditions()
{
	if (m_NumberOfPellets <= 0)
	{
		m_WinStream << "YOU WIN!!!";
		m_GameStateLabel.getComponent<UILabel>().SetLabelText(m_WinStream.str(), "arial");
		Game::m_sIsRunning = false;
	}
	if (m_Pacman.getComponent<PlayerController>().GetLives() <= 0)
	{
		m_WinStream << "GAME OVER";
		m_GameStateLabel.getComponent<UILabel>().SetLabelText(m_WinStream.str(), "arial");
		Game::m_sIsRunning = false;
	}
}