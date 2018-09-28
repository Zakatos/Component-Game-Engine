#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent;

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel);
	
	~ProjectileComponent();
	void init() override;
	void update() override;
private:

	TransformComponent* m_pTransform;
	
	int m_Range = 0;
	int m_Speed = 0;
	int m_Distance = 0;
	Vector2D m_Velocity;

};
