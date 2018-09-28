#pragma once
#include <functional>

class Callback
{
public:
	explicit Callback(const std::string& name, const std::function<void()>& function);
	~Callback() = default;

	void operator()() const;
	friend bool operator==(const Callback& left, const Callback& right);
	friend bool operator<(const Callback& left, const Callback& right);

	/*Callback(const Callback& other) = delete;
	Callback(Callback&& other) = delete;
	Callback& operator=(const Callback& other) = delete;
	Callback& operator=(Callback&& other) = delete;*/

private:
	std::string m_Name;
	std::function<void()> m_Function;
};