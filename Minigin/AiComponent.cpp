#include "MiniginPCH.h"
#include "AiComponent.h"
#include "Structs.h"
#include "Collision.h"
#include "GhostPhysicsComponent.h"
#include "ThreadComponent.h"
AiComponent::~AiComponent()
{
	//m_GhostThread.Stop();
	/*if (m_Thread.joinable())
	{
		m_Thread.join();
	}*/
}

void AiComponent::init()
{
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
	m_pSprite = &m_pEntity->getComponent<SpriteComponent>();
	m_pPhysics = &m_pEntity->getComponent<GhostPhysicsComponent>();
	m_StartPosition = Vector2D(390.f, 320.f);
	m_State = State::Wandering;
	m_pThread = &m_pEntity->getComponent<ThreadComponent>();
	
	//m_GhostThread.AddTask(std::bind(&AiComponent::update, this));
	//m_GhostThread.AddTask(std::bind(&AiComponent::Wander, this));
	//m_GhostThread.AddTask(std::bind(&AiComponent::Scared, this));
	//m_GhostThread.StartTask();	
	//m_Thread = std::thread(&AiComponent::Wander, this);
}

void AiComponent::update()
{
	auto lastLocation = m_pTransform->GetPosition();
	
	m_pPhysics->SetVelocity(Vector2D(0.f, -1.f));
	
		switch (m_State)
		{
		case State::Wandering:
			Wander();
			break;
		case State::Chasing:
			Chase();
			break;
		case State::Scared:
			Scared();
			break;
		case State::Dead:

			break;
		}
		
}
	


void AiComponent::SetState(State state)
{
	m_State = state;
}
void AiComponent::SetDirection(Direction direction)
{
	if(m_pEntity->hasComponent<AiComponent>())
	m_direction = direction;
}
void AiComponent::Wander()
{
	//std::lock_guard<std::mutex> mlock(m_Mutex);
	//if (m_GhostThread.HasFinished()) {
		m_pSprite->setTex(m_SpriteName);
		switch (m_direction)
		{
		case Direction::Up:
			m_pPhysics->SetVelocity(Vector2D(0.f, -0.5f));
			break;
		case Direction::Down:
			m_pPhysics->SetVelocity(Vector2D(0.f, 0.5f));
			break;
		case Direction::Left:
			m_pPhysics->SetVelocity(Vector2D(-0.5f, 0.0f));
			break;
		case  Direction::Right:
			m_pPhysics->SetVelocity(Vector2D(0.5f, 0.0f));
			break;
		}
		//m_GhostThread.StartTask();
	//}
}
void AiComponent::Chase()
{
	
}
void AiComponent::HandleDeath()
{
	m_pPhysics->SetLastPos(m_StartPosition);
	m_pTransform->Translate(m_StartPosition);
}

void AiComponent::CheckPlayerCollision(std::vector<Entity*>& players)
{
	
	for (auto& p : players)
	{
		if(p->getComponent<PlayerController>().GetIsEaten())
		{
			Reset();
			p->getComponent<PlayerController>().SetisEaten(false);
		}
		if (p->getComponent<PlayerController>().GetIsPowered())
		{
			m_pSprite->setTex("ScaredGhost");
			SetState(State::Scared);		
		}
		else
		{
			SetState(State::Wandering);
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


void AiComponent::Scared()
{
	//if (m_GhostThread.HasFinished())
	//{
		switch (m_direction)
		{
		case Direction::Up:
			m_pPhysics->SetVelocity(Vector2D(0.0f, -0.5f));
			break;
		case Direction::Down:
			m_pPhysics->SetVelocity(Vector2D(0.0f, 0.5f));
			break;
		case Direction::Left:
			m_pPhysics->SetVelocity(Vector2D(-0.5f, 0.0f));
			break;
		case  Direction::Right:
			m_pPhysics->SetVelocity(Vector2D(0.5f, 0.0f));
			break;
		}
		//m_GhostThread.StartTask();
	//}
}

void AiComponent::Reset()
{
	m_pTransform->Translate(m_StartPosition);
}

void AiComponent::setSpriteName(std::string name)
{
	m_SpriteName = name;
}

const Direction& AiComponent::GetDirection() const
{
	return m_direction;
}