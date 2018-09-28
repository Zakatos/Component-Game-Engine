#pragma once

#include "PhysicsComponent.h"


class PlayerPhysicsComponent final : public PhysicsComponent
{
public:
	~PlayerPhysicsComponent();
	void init() override;
	void update() override;
	void GetCollisionInformation( const std::vector<Entity*>& colliders);
	
private:
	void CheckForCollision();	
};

