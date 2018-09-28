#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	//using static to ensure this function returns
	//the same unique lastid instance
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	//every time we call this function with a specific type 'T'
	//we are actually calling an instantiation of this template,
	//with its own unique static 'typeID' variable.

	//upon calling this function for the first time with a specific
	//type 'T1', 'typeID' will be initialized with a unique ID.
	//Subsequent calls with the same type 'T1' will return the same ID.

	//using static assert to make sure this function 
	//is only called with types that inherit from 'Component
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

//Creating a sequence of bits that can help us 
//check whether or not an entity has a certain component type

//With a simple and efficient "bitwise and", we can check if a certain
//entity has a component

//When we assign an id number to every component type , we can
//store components in a linear array so that we can efficiently 
//get a certain component type from an entity

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* m_pEntity;

	virtual void init() {}
	virtual void update() {}
	//virtual void draw() {}
	virtual ~Component() {}
};

class Entity
{
private:

	Manager& m_Manager;
	//Keeping a boolean to keep track whether the entity is still alive
	bool m_IsActive = true;
	std::vector<std::unique_ptr<Component>> m_Components;

	ComponentArray m_ComponentArray;
	ComponentBitSet m_ComponentBitSet;
	GroupBitset m_GroupBitSet;

public:
	
	Entity(Manager& mManager) : m_Manager(mManager) {}

	void update()
	{
		for (auto& c : m_Components) c->update();
	}
	/*void draw() 
	{
		for (auto& c : m_Components) c->draw();
	}*/

	bool isActive() const { return m_IsActive; }
	void destroy() { m_IsActive = false; }
	//Groups will be handled at runtime,
	//therefore we will pass groups as a function argument
	bool hasGroup(Group mGroup)
	{
		return m_GroupBitSet[mGroup];
	}
	//To add/remove groups we alter the bitset
	//in these methods and tell the m_Manager what we
	//we are doing, so that the m_Manager can internally
	//store this entity in its grouped containers
	
	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		m_GroupBitSet[mGroup] = false;
	}

	//querying the bitset to check if the entity
	//has a component
	template <typename T> bool hasComponent() const
	{
		return m_ComponentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		//setting the parent entity of the constructor
		//to the current entity
		c->m_pEntity = this;
		
		//wrapping the raw pointer to prevent memory leaks
		std::unique_ptr<Component>uPtr { c };
		
		m_Components.emplace_back(std::move(uPtr));

		//When we add a component of type 'T'we add it to
		// the bitset and to the array
		m_ComponentArray[getComponentTypeID<T>()] = c;
		m_ComponentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		//TODO
		//Add assert?
		auto ptr(m_ComponentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> m_Entities;
	//We store entities in groups by creating "group buckets"
	//in an array
	std::array<std::vector<Entity*>, maxGroups> m_GroupedEntities;
public:
	void update()
	{
		for (auto& e : m_Entities) e->update();
	}
	/*void draw()
	{
		for (auto& e : m_Entities) e->draw();
	}*/
	//refresh should be called before the update, removing
	//dead entities and entities with incorrect groups from the buckets
	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(m_GroupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(m_Entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		m_GroupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return m_GroupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity *e = new Entity(*this);
		std::unique_ptr<Entity> uPtr { e };
		m_Entities.emplace_back(std::move(uPtr));
		return *e;
	}
};