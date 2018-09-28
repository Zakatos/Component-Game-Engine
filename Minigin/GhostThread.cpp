#include "MiniginPCH.h"
#include "GhostThread.h"

GhostThread::GhostThread()
	: m_Tasks(),
	m_IsRunning(true),
	m_DoWork(false),
	m_Mutex(),
	m_Condition(),
	m_Thread(&GhostThread::RunTask, this)
{
}

GhostThread::~GhostThread()
{
	if (m_Thread.joinable())
		m_Thread.join();
}

void GhostThread::StartTask()
{
	std::lock_guard<std::mutex> guard(m_Mutex);

	m_IsRunning = true;
	m_DoWork = true;

	m_Condition.notify_one();

}

void GhostThread::Stop()
{
	m_IsRunning = false;
}

bool GhostThread::HasFinished() const
{
	return !m_DoWork;
}

void GhostThread::AddTask(const std::function<void()>& task)
{
	m_Tasks.push_back(task);
}

void GhostThread::RunTask()
{
	while (m_IsRunning) {
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Condition.wait(lock, std::bind(&GhostThread::m_DoWork, this));

		for (const std::function<void()>& task : m_Tasks) 
		{
			task();
		}

		m_DoWork = false;
	}
}