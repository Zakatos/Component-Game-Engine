#include "MiniginPCH.h"
#include "ECS/ProjectileComponent.h"


ProjectileComponent::ProjectileComponent(int rng, int sp, Vector2D vel) : m_Range(rng), m_Speed(sp), m_Velocity(vel)
{
	
}
ProjectileComponent::~ProjectileComponent()
{
	
}

void ProjectileComponent::init()
{
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
	m_pTransform->SetVelocity(m_Velocity);
}


void ProjectileComponent::update()
{
	m_Distance += m_Speed;

	if (m_Distance > m_Range)
	{
		std::cout << "Out of Range" << std::endl;
		m_pEntity->destroy();
	}
	/*else if (m_pTransform->m_Position.m_X > Game::Camera.x + Game::Camera.w ||
	m_pTransform->m_Position.m_X < Game::Camera.x ||
	m_pTransform->m_Position.m_Y > Game::Camera.y + Game::Camera.h ||
	m_pTransform->m_Position.m_Y < Game::Camera.y)*/
	{
		std::cout << "Out of bounds!" << std::endl;
		m_pEntity->destroy();
	}
}


