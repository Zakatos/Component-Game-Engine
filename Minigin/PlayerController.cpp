#include "MiniginPCH.h"
#include "./ECS/PlayerController.h"
#include "InputManager.h"
#include "Command.h"
#include "Collision.h"
#include "PlayerPhysicsComponent.h"
#include "InputComponent.h"


PlayerController::~PlayerController()
{
	
}

void PlayerController::init()
{
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
	m_pSprite = &m_pEntity->getComponent<SpriteComponent>();
	m_Physics = &m_pEntity->getComponent<PlayerPhysicsComponent>();
	m_InputComponent = &m_pEntity->getComponent<InputComponent>();
	m_Lives = 3;
	m_StartPoint = Vector2D(400.0f, 450.f);
	m_Physics->SetVelocity(Vector2D(0.0f, 0.0f));
}

void PlayerController::update()
{
	
	m_pEntity->getComponent<InputComponent>().ProcessInput();
	PowerUp();
		switch (m_Direction)
		{
		case Direction::Left:
			m_Physics->SetVelocity(Vector2D(-0.9f, 0.0f));
			m_pSprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			break;
		case Direction::Up:			
			m_Physics->SetVelocity(Vector2D(0.0f, -0.9f));					
			break;
		case Direction::Right:
			m_Physics->SetVelocity(Vector2D(0.9f, 0.0f));		
			break;
		case Direction::Down:
			m_Physics->SetVelocity(Vector2D(0.0f, 0.9f));			
			break;
		default:
			break;
		}
	
}


void PlayerController::SetDirection(Direction direction)
{
	m_Direction = direction;
}

bool PlayerController::GetIsPowered() const
{
	return m_IsPowered;
}

void PlayerController::PowerUp()
{
	if (m_IsPowered)
	{
		m_PoweredTimer += Game::m_sElapsedsec;

		if (m_PoweredTimer > 10.0f)
		{
			m_IsPowered = false;
			m_PoweredTimer = 0.0f;
		}
	}
}


void PlayerController::CheckPelletsCollisions(std::vector<Entity*>& pellets, std::vector<Entity*>& powerPellets,int& numberOfPellets)
{
	for (auto& p : powerPellets)
	{
		if (Collision::AABB(m_pEntity->getComponent<ColliderComponent>().GetCollider(), p->getComponent<ColliderComponent>().GetCollider()))
		{
			--numberOfPellets;
			m_IsPowered = true;
			p->destroy();		
		}
	}

	for (auto& p : pellets)
	{

		if (Collision::AABB(m_pEntity->getComponent<ColliderComponent>().GetCollider(), p->getComponent<ColliderComponent>().GetCollider()))
		{	
		--numberOfPellets;
		p->destroy();	
		}
	
	}
}

const int& PlayerController::GetLives() const
{
	return m_Lives;
}

void PlayerController::Eaten()
{
	m_Physics->SetLastPos(m_StartPoint);
	m_pTransform->Translate(m_StartPoint);
	--m_Lives;
	m_isEaten = true;
}

bool PlayerController::GetIsEaten() const
{
	return m_isEaten;
}

void PlayerController::SetisEaten(bool isEaten)
{
	m_isEaten = isEaten;
}