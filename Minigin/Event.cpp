#include "MiniginPCH.h"
#include "Event.h"


void Event::AddListener(const Callback& pCallback)
{
	m_Listeners.insert(pCallback);
}

void Event::RemoveListener(const Callback& pCallback)
{
	auto it = m_Listeners.find(pCallback);

	if (it != m_Listeners.end())
		m_Listeners.erase(it);
}

void Event::Invoke()
{
	for (const Callback& callback : m_Listeners) {
		callback();
	}
}