#pragma once


#include <set>
#include "Callback.h"

class Event
{
public:
	Event() = default;
	~Event() = default;

	void AddListener(const Callback& callback);
	void RemoveListener(const Callback& callback);
	void Invoke();

#pragma region Event Names
	static std::string EatGhost() { return "EatGhost"; }
	static std::string EatPellet() { return "EatPellet"; }
	static std::string EatPower() { return "EatPower"; }
	static std::string EatFruit() { return "EatFruit"; }
	static std::string LostPower() { return "LostPower"; }
	static std::string Die() { return "Die"; }
	static std::string GameOver() { return "GameOver"; }
#pragma endregion Event Names

private:
	std::set<Callback> m_Listeners;
};
