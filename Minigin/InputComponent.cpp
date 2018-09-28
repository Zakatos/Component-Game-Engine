#include "MiniginPCH.h"
#include "InputComponent.h"


InputComponent::InputComponent() 
{
}

InputComponent::~InputComponent()
{	
	
}

InputComponent::InputComponent(ControllerButton left, ControllerButton up, ControllerButton right, ControllerButton down)
{

	
	m_Inputs[left] = std::make_shared<MoveLeftCommand>();
	m_Inputs[up] = std::make_shared<MoveUpCommand>();
	m_Inputs[right] = std::make_shared<MoveRightCommand>();
	m_Inputs[down] = std::make_shared<MoveDownCommand>();
}

void InputComponent::update()
{

}


void InputComponent::ProcessInput()
{
	auto& input = InputManager::GetInstance();
	input.ProcessInput();
	for (auto p : m_Inputs)
	{
		if (input.IsPressed(p.first))
		{
			p.second->Execute(m_pEntity);
		}
	}
}


