#pragma once
#include "PhysicsComponent.h"



class GhostPhysicsComponent final : public PhysicsComponent
{
public:
	~GhostPhysicsComponent();
	void init() override;
	void update() override;
	void GetCollisionInformation(const std::vector<Entity*>& colliders);
private:
	void CheckForCollision();
};


