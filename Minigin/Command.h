#pragma once
#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "ECS/Components.h"
#include <map>
#include "Structs.h"


class PlayerController;

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute(Entity* entity) = 0;
};

class MoveRightCommand final : public Command
{
public:
	virtual void Execute(Entity* entity) override;
};

class MoveLeftCommand final : public Command
{
public:
	virtual void Execute(Entity* entity) override;
	
};

class MoveUpCommand final :public Command
{
public:
	virtual void Execute(Entity* entity) override;
	
};

class MoveDownCommand final :public Command
{
public:
	virtual void Execute(Entity* entity) override;
	
};

class MoveUiLeft final :public Command
{
public:
	virtual void Execute(Entity* entity) override;

};
class KeyFirstUi final :public Command
{
public:
	virtual void Execute(Entity* entity) override;

};
class KeySecondUi final :public Command
{
public:
	virtual void Execute(Entity* entity) override;

};
class KeyThirdUi final :public Command
{
public:
	virtual void Execute(Entity* entity) override;

};
class ConfirmSelection final :public Command
{
public:
	virtual void Execute(Entity* entity) override;

};


class MoveUiRight final :public Command
{
public:
	virtual void Execute(Entity* entity) override;

};

	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		DpadUp,
		DpadDown,
		DpadRight,
		DpadLeft,
		ArrowLeft,
		ArrowRight,
		W,
		A,
		S,
		D
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		bool ProcessInput();
		bool IsPressed(ControllerButton button);
		bool IsKeyPressed(int key);
		//Command* HandleInput();
		std::shared_ptr<Command> HandleInput();
		void Clear();
	private:
		XINPUT_STATE currentState{};
		/*Command* m_pRight = new MoveRightCommand();
		Command* m_pLeft = new MoveLeftCommand();
		Command* m_pUp = new MoveUpCommand();
		Command* m_pDown = new MoveDownCommand();
		Command* m_UiLeft = new MoveUiLeft();
		Command* m_UiRight = new MoveUiRight();
		Command* m_FirstSelection = new KeyFirstUi;
		Command* m_SecondSelection = new KeySecondUi;
		Command* m_ThirdSelection = new KeyThirdUi;
		Command* m_ConfirmSelection = new ConfirmSelection;*/
		std::shared_ptr<Command> m_pRight = std::make_shared<MoveRightCommand>();
		std::shared_ptr<Command> m_pLeft = std::make_shared<MoveLeftCommand>();
		std::shared_ptr<Command> m_pUp = std::make_shared<MoveUpCommand>();
		std::shared_ptr<Command> m_pDown = std::make_shared<MoveDownCommand>();
		std::shared_ptr<Command> m_UiLeft = std::make_shared<MoveUiLeft>();
		std::shared_ptr<Command> m_UiRight = std::make_shared<MoveUiRight>();
		std::shared_ptr<Command> m_FirstSelection = std::make_shared<KeyFirstUi>();
		std::shared_ptr<Command> m_SecondSelection = std::make_shared<KeySecondUi>();
		std::shared_ptr<Command> m_ThirdSelection = std::make_shared<KeyThirdUi>();
		std::shared_ptr<Command> m_ConfirmSelection = std::make_shared<ConfirmSelection>();
		std::map<int, bool> m_KeyMap;

	};



