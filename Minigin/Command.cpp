#include "MiniginPCH.h"
#include "Command.h"
#include <SDL.h>
#include <XInput.h>
#include "ECS/Components.h"
#include "Structs.h"
#include "CursorComponent.h"
#include "GhostPlayerController.h"
#pragma comment(lib, "XInput.lib") 

bool InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_KeyMap[e.key.keysym.sym] = true;
		}
		if (e.type == SDL_KEYUP)
		{
			m_KeyMap[e.key.keysym.sym] = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool InputManager::IsPressed(ControllerButton button) 
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DpadUp:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::DpadDown:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::DpadRight:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::DpadLeft:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::W:
		return IsKeyPressed(SDLK_w);
	case ControllerButton::S:
		return IsKeyPressed(SDLK_s);
	case ControllerButton::A:
		return IsKeyPressed(SDLK_a);
	case ControllerButton::D:
		return IsKeyPressed(SDLK_d);
	default: 
		return false;
	}

}

bool InputManager::IsKeyPressed(int key)
{
	return m_KeyMap[key];
}

std::shared_ptr<Command> InputManager::HandleInput()
{
	//controller
	if (IsPressed(ControllerButton::DpadRight)) return m_pRight;
	if (IsPressed(ControllerButton::DpadLeft)) return m_pLeft;
	if (IsPressed(ControllerButton::DpadUp)) return m_pUp;
	if (IsPressed(ControllerButton::DpadDown)) return m_pDown;

	if (IsKeyPressed(SDLK_LEFT)) return m_UiLeft;
	if (IsKeyPressed(SDLK_RIGHT)) return m_UiRight;

	//Keyboard
	if (m_KeyMap[SDLK_w])
	{
		return m_pUp;
	}

	if (m_KeyMap[SDLK_s])
	{
		return m_pDown;
	}
	if (m_KeyMap[SDLK_a])
	{
		return m_pLeft;
	}
	if (m_KeyMap[SDLK_d])
	{
		return m_pRight;
	}
	if (m_KeyMap[SDLK_1])
	{
		return m_FirstSelection;
	}
	if (m_KeyMap[SDLK_2])
	{
		return m_SecondSelection;
	}
	if (m_KeyMap[SDLK_3])
	{
		return m_ThirdSelection;
	}
	if (m_KeyMap[SDLK_RETURN])
	{
		return m_ConfirmSelection;
	}


	return nullptr;
}

void InputManager::Clear()
{
	/*delete m_pRight;
	m_pRight = nullptr;

	delete m_pLeft;
	m_pLeft = nullptr;

	delete m_pUp;
	m_pUp = nullptr;

	delete m_pDown;
	m_pDown = nullptr;

	delete m_UiLeft;
	m_UiLeft = nullptr;

	delete m_UiRight;
	m_UiRight = nullptr;

	delete m_FirstSelection;
	m_FirstSelection = nullptr;

	delete m_SecondSelection;
	m_SecondSelection = nullptr;

	delete m_ThirdSelection;
	m_ThirdSelection = nullptr;

	delete m_ConfirmSelection;
	m_ConfirmSelection = nullptr;*/

}

void MoveRightCommand::Execute(Entity* entity)
{
	if (entity->hasComponent<PlayerController>())
	{
		entity->getComponent<PlayerController>().SetDirection(Direction::Right);
	}
	if (entity->hasComponent<GhostPlayerController>())
	{
		entity->getComponent<GhostPlayerController>().SetDirection(Direction::Right);
	}
}

void MoveLeftCommand::Execute(Entity* entity)
{
	if (entity->hasComponent<PlayerController>())
	{
		entity->getComponent<PlayerController>().SetDirection(Direction::Left);
	}
	if (entity->hasComponent<GhostPlayerController>())
	{
		entity->getComponent<GhostPlayerController>().SetDirection(Direction::Left);
	}
	
}

void MoveUpCommand::Execute(Entity* entity)
{
	if (entity->hasComponent<PlayerController>())
	{
		entity->getComponent<PlayerController>().SetDirection(Direction::Up);
	}
	if (entity->hasComponent<GhostPlayerController>())
	{
		entity->getComponent<GhostPlayerController>().SetDirection(Direction::Up);
	}
	
}

void MoveDownCommand::Execute(Entity* entity)
{
	if (entity->hasComponent<PlayerController>())
	{
		entity->getComponent<PlayerController>().SetDirection(Direction::Down);
	}
	if (entity->hasComponent<GhostPlayerController>())
	{
		entity->getComponent<GhostPlayerController>().SetDirection(Direction::Down);
	}
	
}

void MoveUiLeft::Execute(Entity* entity)
{
	if (entity->hasComponent<CursorComponent>())
	{
		entity->getComponent<CursorComponent>().DecrementCursorPosition();
	}
}


void MoveUiRight::Execute(Entity* entity)
{
	if (entity->hasComponent<CursorComponent>())
	{
		entity->getComponent<CursorComponent>().IncrementCursorPosition();
	}
}

void KeyFirstUi::Execute(Entity* entity)
{
	if (entity->hasComponent<CursorComponent>())
	{
		entity->getComponent<CursorComponent>().SetCursorPosition(1);
	}
}

void KeySecondUi::Execute(Entity* entity)
{
	if (entity->hasComponent<CursorComponent>())
	{
		entity->getComponent<CursorComponent>().SetCursorPosition(2);
	}
}

void KeyThirdUi::Execute(Entity* entity)
{
	if (entity->hasComponent<CursorComponent>())
	{
		entity->getComponent<CursorComponent>().SetCursorPosition(3);
	}
}

void ConfirmSelection::Execute(Entity* entity)
{
	if (entity->hasComponent<CursorComponent>())
	{
		entity->getComponent<CursorComponent>().SetGamescene();
	}
}
