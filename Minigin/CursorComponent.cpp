#include "MiniginPCH.h"
#include "CursorComponent.h"


CursorComponent::CursorComponent()
{
}


CursorComponent::~CursorComponent()
{
	
}

void CursorComponent::init()
{
	m_CursorPosition = 1;
	m_pTransform = &m_pEntity->getComponent<TransformComponent>();
}
void CursorComponent::update()
{
	m_Command = InputManager::GetInstance().HandleInput();
	if (m_Command) m_Command->Execute(m_pEntity);

		switch (m_CursorPosition)
	{
		case 1:
			m_pTransform->Translate(295.f, 400.f);
			break;
		case 2:
			m_pTransform->Translate(405.f, 400.f);
			break;
		case 3:
			m_pTransform->Translate(520.f, 400.f);
			break;
		default:
			break;
		}
}


void CursorComponent::IncrementCursorPosition()
{
	if (m_CursorPosition != 2)
	{
		
		m_CursorPosition += 1;
	}
	if(m_CursorPosition>2)
	{
		
		m_CursorPosition = 2;
	}
}
void CursorComponent::DecrementCursorPosition()
{
	if (m_CursorPosition != 0)
	{
		
		m_CursorPosition -= 1;
	}
	if (m_CursorPosition <0)
	{
		
		m_CursorPosition = 0;
	}
}

void CursorComponent::SetCursorPosition(int cursorpos)
{
	m_CursorPosition = cursorpos;
}

void CursorComponent::SetGamescene()
{
	Game::m_GameSceneNum = m_CursorPosition;
}