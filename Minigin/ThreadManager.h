#pragma once
#include "Singleton.h"
#include "ThreadRaii.h"
#include <memory>
#include <vector>

class ThreadManager : public Singleton<ThreadManager>
{
public:
	void AddThread(std::shared_ptr<ThreadRaii> thread)
	{
		m_Threads.push_back(thread);
	}

private:
	std::vector<std::shared_ptr<ThreadRaii>> m_Threads;
};
