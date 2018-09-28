#pragma once
#include <thread>
#include <memory>

class ThreadRaii
{
	
public:
	ThreadRaii(std::shared_ptr<std::thread> threadObj) : m_spthread(threadObj)
	{

	}
	~ThreadRaii()
	{
		if (m_spthread->joinable())
		{
			m_spthread->detach();
		}
	}
private:
	std::shared_ptr<std::thread> m_spthread;
};

