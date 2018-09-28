#include "MiniginPCH.h"
#include "ECS.h"

void Entity::addGroup(Group mGroup)
{
	m_GroupBitSet[mGroup] = true;
	m_Manager.AddToGroup(this, mGroup);
}