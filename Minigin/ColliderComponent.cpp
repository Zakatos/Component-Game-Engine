#include "MiniginPCH.h"
#include "ECS/ColliderComponent.h"
#include "RendererComponent.h"


ColliderComponent::ColliderComponent(const std::string& t)
	:m_Tag(t)
{
	
}



ColliderComponent::ColliderComponent(const std::string& t, int xpos, int ypos, int size)
	:m_Tag(t)
{
	
	m_Collider.x = xpos;
	m_Collider.y = ypos;
	m_Collider.h = m_Collider.w = size;
}

ColliderComponent::~ColliderComponent()
{
	SDL_DestroyTexture(m_pTex);
	//delete m_pRenderer;
	//m_pRenderer = nullptr;
}

void ColliderComponent::init()
{
	if (!m_pEntity->hasComponent<TransformComponent>())
	{
		m_pEntity->addComponent<TransformComponent>();
	}

	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
	m_pRenderer = &m_pEntity->getComponent<RendererComponent>();
	m_pTex = m_pRenderer->LoadTexture("assets/coltex.png");
	m_SrcR = { 0, 0, 32, 32 };
	m_destR = { m_Collider.x, m_Collider.y, m_Collider.w, m_Collider.h };
}

void ColliderComponent::update()
{
	if (m_Tag != "terrain")
	{

		m_Collider.x = static_cast<int>(m_pTransform->GetPosition().m_X);
		m_Collider.y = static_cast<int>(m_pTransform->GetPosition().m_Y);
		m_Collider.w = m_pTransform->GetWidth() * m_pTransform->GetScale();
		m_Collider.h = m_pTransform->GetHeight() * m_pTransform->GetScale();
		
	}

	m_destR.x = m_Collider.x;
	m_destR.y = m_Collider.y;
}

void ColliderComponent::draw()
{
	m_pRenderer->Draw(m_pTex, m_SrcR, m_destR, SDL_FLIP_NONE);
}

