#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "Command.h"
#include "Structs.h"
#include "../InputComponent.h"

class TransformComponent;
class SpriteComponent;
class Command;
class PlayerPhysicsComponent;
class InputComponent;

class PlayerController final : public Component
{
public:

	~PlayerController();
	void init() override;
	void update() override;
	void SetDirection(Direction direction);
	void PowerUp();
	bool GetIsPowered() const;
	void Eaten();
	void CheckPelletsCollisions(std::vector<Entity*>& pellets, std::vector<Entity*>& powerPellets, int& numberOfPellets);
	const int& GetLives() const;
	bool GetIsEaten() const;
	void SetisEaten(bool isEaten);
	PlayerController& operator=(const PlayerController& other) = delete;
	PlayerController& operator=(PlayerController&& other) = delete;
private:
	TransformComponent* m_pTransform = nullptr;
	SpriteComponent* m_pSprite = nullptr;
	PlayerPhysicsComponent* m_Physics = nullptr;
	InputComponent* m_InputComponent = nullptr;
	Direction m_Direction = Direction::Up;
	bool m_IsPowered = false;
	bool m_isEaten = false;
	float m_PoweredTimer = 0.0f;
	int m_Lives = 0;
	Vector2D m_StartPoint;

};