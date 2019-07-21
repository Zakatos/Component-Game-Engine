#include "MiniginPCH.h"
#include "GhostPlayerController.h"
#include "Structs.h"
#include "Collision.h"

GhostPlayerController::GhostPlayerController()
{
}


GhostPlayerController::~GhostPlayerController()
{
}

void GhostPlayerController::init()
{
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
	m_pSprite = &m_pEntity->getComponent<SpriteComponent>();
	m_pPhysics = &m_pEntity->getComponent<GhostPhysicsComponent>();
	m_InputComponet = &m_pEntity->getComponent<InputComponent>();
	m_StartPosition = Vector2D(390.f, 320.f);
	m_pPhysics->SetVelocity(Vector2D(0.f, 0.0f));
	
	
}

void GhostPlayerController::update()
{
	m_pEntity->getComponent<InputComponent>().ProcessInput();

	switch (m_direction)
	{
	case Direction::Up:
		m_pPhysics->SetVelocity(Vector2D(0.f, -0.8f));
		break;
	case Direction::Down:
		m_pPhysics->SetVelocity(Vector2D(0.f, 0.8f));

		break;
	case Direction::Left:
		m_pPhysics->SetVelocity(Vector2D(-0.8f, 0.0f));

		break;
	case  Direction::Right:
		m_pPhysics->SetVelocity(Vector2D(0.8f, 0.0f));

		break;
	}		
	
}


void GhostPlayerController::SetDirection(Direction direction)
{
	m_direction = direction;
}
void GhostPlayerController::Wander()
{
	m_pSprite->setTex(m_SpriteName);
		
}

void GhostPlayerController::HandleDeath()
{
	m_pTransform->Translate(m_StartPosition);
}

void GhostPlayerController::CheckPlayerCollision(std::vector<Entity*>& players)
{
	
	for (auto& p : players)
	{

		if (p->getComponent<PlayerController>().GetIsEaten())
		{
			Reset();
			p->getComponent<PlayerController>().SetisEaten(false);
		}

		if (p->getComponent<PlayerController>().GetIsPowered())
		{
			m_pSprite->setTex("ScaredGhost");			
		}
		else if (!p->getComponent<PlayerController>().GetIsPowered() || p->getComponent<PlayerController>().GetIsEaten())
		{
			m_pSprite->setTex(m_SpriteName);
		}
		if (Collision::AABB(m_pEntity->getComponent<ColliderComponent>().GetCollider(), p->getComponent<ColliderComponent>().GetCollider()))
		{
			if (p->getComponent<PlayerController>().GetIsPowered())
			{
				HandleDeath();
			}
			if (!p->getComponent<PlayerController>().GetIsPowered())
			{
				p->getComponent<PlayerController>().Eaten();
				Reset();
			}
		}
	}

}


void GhostPlayerController::Scared()
{
	m_pEntity->getComponent<InputComponent>().ProcessInput();
	m_pSprite->setTex("ScaredGhost");
	switch (m_direction)
	{
	case Direction::Up:
		m_pPhysics->SetVelocity(Vector2D(0.0f, -0.9f));
		
		break;
	case Direction::Down:
		m_pPhysics->SetVelocity(Vector2D(0.0f, 0.9f));
		
		break;
	case Direction::Left:
		m_pPhysics->SetVelocity(Vector2D(-0.9f, 0.0f));
		
		break;
	case  Direction::Right:
		m_pPhysics->SetVelocity(Vector2D(0.9f, 0.0f));
	
		break;
	}
}

void GhostPlayerController::Reset()
{
	m_pTransform->Translate(m_StartPosition);
}

void GhostPlayerController::setSpriteName(std::string name)
{
	m_SpriteName = name;
}

