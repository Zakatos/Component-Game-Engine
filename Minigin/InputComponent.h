#pragma once
#include "ECS/Components.h"
#include "Command.h"

class Command;
class InputManager;
enum class ControllerButton;

class InputComponent final : public Component
{
public:
	InputComponent();
	explicit InputComponent(ControllerButton left, ControllerButton up, ControllerButton right, ControllerButton down);
	~InputComponent();
	void ProcessInput();
	void update() override;

	InputComponent(const InputComponent& obj) = delete;
	InputComponent& operator=(const InputComponent& obj) = delete;
	InputComponent(const InputComponent&& obj) = delete;
	InputComponent& operator=(const InputComponent&& obj) = delete;

private:
	std::map<ControllerButton, std::shared_ptr<Command>> m_Inputs;
	
};