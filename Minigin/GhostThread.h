#pragma once

#include <thread>
#include <functional>
#include <mutex>

class GhostThread
{
public:
	GhostThread();
	~GhostThread();

	void StartTask();
	void Stop();
	bool HasFinished() const;
	void AddTask(const std::function<void()>& task);
	GhostThread(const GhostThread& other) = delete;
	GhostThread(GhostThread&& other) = delete;
	GhostThread& operator=(const GhostThread& other) = delete;
	GhostThread& operator=(GhostThread&& other) = delete;
private:
	void RunTask();

	std::vector<std::function<void()>> m_Tasks;
	bool m_IsRunning;
	bool m_DoWork;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
	std::thread m_Thread;
};