#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include <SDL_hints.h>
#include <SDL.h>

//enum class Input : int
//{
//	P1_Up = 0,
//	P1_Down = 1,
//	P1_Left = 2,
//	P1_Right = 3,
//
//	P2_Up = 4,
//	P2_Down = 5,
//	P2_Left = 6,
//	P2_Right = 7,
//};
//
//struct InputAction
//{
//	Input id;
//	int bitMask;
//	int playerId;
//	bool useGamepad;
//};
//
//
//class InputManager final : public Singleton<InputManager>
//{
//public:
//	bool Update();
//	void AddInputAction(const InputAction& action);
//	bool IsActionTriggered(const Input id);
//
//private:
//	static const int m_NrOfPlayers = 2;
//	XINPUT_STATE m_GamepadStates[m_NrOfPlayers];
//
//	const Uint8* m_pKeyboard{ SDL_GetKeyboardState(nullptr) };
//
//	std::map<int, InputAction> m_InputActions{};
//};