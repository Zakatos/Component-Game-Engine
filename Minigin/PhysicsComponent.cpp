#include "MiniginPCH.h"
#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{
}


PhysicsComponent::~PhysicsComponent()
{
	/*for (std::vector< Entity* >::iterator it = m_pWallColliders.begin(); it != m_pWallColliders.end(); ++it)
	{
		delete (*it);
	}
	m_pWallColliders.clear();*/
}

void PhysicsComponent::init()
{
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
}

void PhysicsComponent::update()
{
	
}


void PhysicsComponent::SetVelocity(Vector2D velocity)
{
	m_Velocity = velocity;
}

void PhysicsComponent::SetLastPos(Vector2D lastpost)
{
	m_LastPos = lastpost;
}