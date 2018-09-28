#include "MiniginPCH.h"
#include "Game.h"
#include "Command.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  






int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	UNUSED(argc);
	UNUSED(argv);
	const int msPerFrame = 16;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	bool takeInput = true;
	
	auto upGame = std::make_unique<Game>();
	
	upGame->init("GameWindow", 800, 640, false);
	auto& input = InputManager::GetInstance();
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;
	while (upGame->running())
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
		
		lastTime = currentTime;
		lag += deltaTime;
		
		
		takeInput = input.ProcessInput();
		while (lag >= msPerFrame)
		{			
			upGame->update();		
			lag -= msPerFrame;
		}
		upGame->render();
	}
	
	upGame->clean();
	
	return 0;
}