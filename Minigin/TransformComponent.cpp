#include "MiniginPCH.h"
#include "ECS/TransformComponent.h"

TransformComponent::TransformComponent()
{
	m_Position.Zero();
}


TransformComponent::TransformComponent(int sc)
{
	m_Position.Zero();
	m_Scale = sc;
}


TransformComponent::TransformComponent(float x, float y)
{
	UNUSED(x);
	UNUSED(y);
	m_Position.Zero();
}


TransformComponent::TransformComponent(float x, float y, int h, int w, int sc)
{
	m_Position.m_X = x;
	m_Position.m_Y = y;
	m_Height = h;
	m_Width = w;
	m_Scale = sc;
}

void TransformComponent::init()
{
	//m_Velocity.Zero();
}


void TransformComponent::update()
{
	//m_Position.m_X += static_cast<int>( m_Speed);
	//m_Position.m_Y += static_cast<int>( m_Speed);
	
}

void TransformComponent::Translate(float x, float y)
{
	m_Position.m_X = x;
	m_Position.m_Y = y;
	
}
void TransformComponent::Translate(const Vector2D& position)
{
	m_Position = position;
}
void TransformComponent::SetScale(int scale)
{
	m_Scale = scale;
}
void TransformComponent::SetHeight(int height)
{
	m_Height = height;
}
void TransformComponent::SetWidth(int Width)
{
	m_Width = Width;
}


void TransformComponent::SetPositionX(float x)
{
	m_Position.m_X = x;
}
void TransformComponent::SetPositionY(float y)
{
	m_Position.m_Y = y;
}
