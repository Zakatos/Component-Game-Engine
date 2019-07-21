#include "MiniginPCH.h"
#include "GhostPhysicsComponent.h"
#include "AiComponent.h"

GhostPhysicsComponent::~GhostPhysicsComponent()
{	
}

void GhostPhysicsComponent::init()
{
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
	m_VectorRate = 0.5f;
}

void GhostPhysicsComponent::update()
{
	CheckForCollision();
	m_pTransform->m_Position.m_X += static_cast<int>(m_Velocity.m_X * 3);
	m_pTransform->m_Position.m_Y += static_cast<int>(m_Velocity.m_Y * 3);
	m_VectorRate += Game::m_sElapsedsec;
	if (m_VectorRate >= m_VectorInterval)
	{
		m_LastPos = m_pEntity->getComponent<TransformComponent>().GetPosition();
		m_VectorRate = 0;
	}

	

}

void GhostPhysicsComponent::GetCollisionInformation(const std::vector<Entity*>& colliders)
{
	m_pWallColliders = colliders;
	
}

void GhostPhysicsComponent::CheckForCollision()
{
	SDL_Rect GhostCol = m_pEntity->getComponent<ColliderComponent>().GetCollider();
	

	for (auto& c : m_pWallColliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().GetCollider();
		if (Collision::AABB(cCol, GhostCol))
		{
			float tempX = m_LastPos.m_X - m_pEntity->getComponent<TransformComponent>().GetPosition().m_X;
			float TempY = m_LastPos.m_Y - m_pEntity->getComponent<TransformComponent>().GetPosition().m_Y;
			if (m_pEntity->hasComponent<AiComponent>())
			{

				Direction tempdir = Direction(rand() % 4);
				if(m_pEntity->getComponent<AiComponent>().GetDirection() == tempdir)
				{
					tempdir = Direction(rand() % 4);
				}
				m_pEntity->getComponent<AiComponent>().SetDirection(tempdir);
			}
			m_pEntity->getComponent<TransformComponent>().Translate(m_pEntity->getComponent<TransformComponent>().GetPosition().m_X + tempX, m_pEntity->getComponent<TransformComponent>().GetPosition().m_Y + TempY);
		}
	}
	
}
