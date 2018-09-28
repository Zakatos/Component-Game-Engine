#pragma once
#include "ECS/Components.h"
#include "GhostPhysicsComponent.h"

class InputComponent;

class GhostPlayerController final : public Component
{
public:
	enum class State
	{
		Wandering,
		Chasing,
		Scared,
		Dead
	};
	GhostPlayerController();
	~GhostPlayerController();
	void init() override;
	void update() override;
	void SetDirection(Direction direction);
	void CheckPlayerCollision(std::vector<Entity*>& players);
	void Scared();
	void Reset();
	void SetState(State state);
	void setSpriteName(std::string name);
	GhostPlayerController& operator=(const GhostPlayerController& other) = delete;
	GhostPlayerController& operator=(GhostPlayerController&& other) = delete;
private:
	void Wander();
	void Chase();
	void HandleDeath();
	TransformComponent* m_pTransform;
	SpriteComponent* m_pSprite;
	InputComponent* m_InputComponet;
	State m_State;
	GhostPhysicsComponent* m_pPhysics;
	std::string m_SpriteName;	
	Direction m_direction;
	Vector2D m_StartPosition;
	Command* m_Command;
};

