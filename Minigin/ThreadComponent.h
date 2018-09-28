#pragma once
#include "ECS/Components.h"


class ThreadComponent final : public Component
{
public:
	ThreadComponent();
	~ThreadComponent();
	void init() override;
	void update() override;
	ThreadComponent(const ThreadComponent& other) = delete;
	ThreadComponent(ThreadComponent&& other) = delete;
	ThreadComponent& operator=(const ThreadComponent& other) = delete;
	ThreadComponent& operator=(ThreadComponent&& other) = delete;
private:

	int m_Counter = 0;
};

