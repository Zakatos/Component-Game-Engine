#pragma once
#include "ECS/Components.h"

class TransformComponent;

class CursorComponent final : public Component
{
public:
	enum CursorPosition
	{
		SinglePlayer,
		TwoPlayerGhost,
		TwoPlayerPacman
	};
	CursorComponent();
	~CursorComponent();
	void IncrementCursorPosition();
	void DecrementCursorPosition();
	void SetCursorPosition(int cursorpos);
	void SetGamescene();
	void init() override;
	void update() override;
	
private:
	TransformComponent * m_pTransform = nullptr;
	std::shared_ptr<Command> m_Command;
	int m_CursorPosition;
	bool m_KeyIsDown = false;
};

