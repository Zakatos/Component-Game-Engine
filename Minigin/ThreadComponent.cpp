#include "MiniginPCH.h"
#include "ThreadComponent.h"
#include "ThreadManager.h"


ThreadComponent::ThreadComponent()
{
}


ThreadComponent::~ThreadComponent()
{
}

void ThreadComponent::init()
{
	std::shared_ptr<std::thread> threadObj = std::make_shared<std::thread>(&ThreadComponent::update, this);
	ThreadManager::GetInstance().AddThread(std::make_shared<ThreadRaii>(threadObj));
}

void ThreadComponent::update()
{
	
}
