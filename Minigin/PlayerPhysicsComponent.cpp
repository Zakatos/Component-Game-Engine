#include "MiniginPCH.h"
#include "PlayerPhysicsComponent.h"



PlayerPhysicsComponent::~PlayerPhysicsComponent()
{

}


void PlayerPhysicsComponent::init()
{
	m_LastPos = Vector2D{ 400.0f,450.f };
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
	m_VectorInterval = 0.2f;
	m_IsColliding = false;
}

void PlayerPhysicsComponent::update()
{
	m_VectorRate += Game::m_sElapsedsec;
	CheckForCollision();
	
	m_pTransform->m_Position.m_X += static_cast<int>(m_Velocity.m_X * 3);
	m_pTransform->m_Position.m_Y += static_cast<int>(m_Velocity.m_Y * 3);
	
	
	if (m_VectorRate >= m_VectorInterval)
	{
		if (!m_IsColliding)
		{
			m_LastPos = m_pEntity->getComponent<TransformComponent>().GetPosition();
		}
		m_VectorRate = 0;
	}

	

}

void PlayerPhysicsComponent::GetCollisionInformation(const std::vector<Entity*>& colliders)
{	
	
	m_pWallColliders = colliders;
}

void PlayerPhysicsComponent::CheckForCollision()
{
	SDL_Rect playerCol = m_pEntity->getComponent<ColliderComponent>().GetCollider();
	Vector2D playerPos = m_pEntity->getComponent<TransformComponent>().GetPosition();
	Vector2D previousVel = m_Velocity;
	for (auto& c : m_pWallColliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().GetCollider();
		if (Collision::AABB(cCol, playerCol))
		{
			float tempX = m_LastPos.m_X - playerPos.m_X;
			float TempY = m_LastPos.m_Y - playerPos.m_Y;
			
			m_pEntity->getComponent<TransformComponent>().Translate(playerPos.m_X + tempX, playerPos.m_Y + TempY);
			m_IsColliding = true;
			SetVelocity(Vector2D(0.0f, 0.0f));
			
		}
		else
		{
			SetVelocity(Vector2D(previousVel.m_X,previousVel.m_Y));
			m_IsColliding = false;
		}


	}



}


