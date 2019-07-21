#pragma once
#include "ECS/Components.h"
#include "Structs.h"
#include "GhostThread.h"

class TransformComponent;
class SpriteComponent;
class GhostPhysicsComponent;
class ThreadComponent;
enum class State
{
	Wandering,
	Chasing,
	Scared,
	Dead
};



class AiComponent final: public Component
{
public:
	
	~AiComponent();
	void init() override;
	void update() override;
	void SetState(State state);
	const Direction& GetDirection() const;
	void SetDirection(Direction direction);
	void CheckPlayerCollision(std::vector<Entity*>& players);
	void Scared();
	void Reset();
	void setSpriteName(const std::string& name);
	AiComponent& operator=(const AiComponent& other) = delete;
	AiComponent& operator=(AiComponent&& other) = delete;
private:
	void Wander();
	void Chase();
	void HandleDeath();
//	GhostThread m_GhostThread;
	TransformComponent* m_pTransform = nullptr;
	SpriteComponent* m_pSprite = nullptr;
	GhostPhysicsComponent* m_pPhysics = nullptr;
	ThreadComponent* m_pThread = nullptr;
	std::string m_SpriteName;
	State m_State = State::Wandering;
	Direction m_direction = Direction::Up;
	Vector2D m_StartPosition;
	//std::thread m_Thread;
	std::mutex m_Mutex;
};

