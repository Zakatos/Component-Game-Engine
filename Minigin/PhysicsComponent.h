#pragma once
#include "ECS/Components.h"
#include "Collision.h"

class TransformComponent;
class ColliderComponent;

class PhysicsComponent  : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	void init() override;
	void update() override;
	const Vector2D& GetVelocity() const { return m_Velocity; }
	const Vector2D& GetLastPos() const { return m_LastPos; }
	void SetLastPos(Vector2D lastpost);
	void SetVelocity(Vector2D velocity);
	PhysicsComponent(const PhysicsComponent& other) = delete;
	PhysicsComponent(PhysicsComponent&& other) = delete;
	PhysicsComponent& operator=(const PhysicsComponent& other) = delete;
	PhysicsComponent& operator=(PhysicsComponent&& other) = delete;
protected:
	Vector2D m_Velocity{1.f,1.f};
	Vector2D m_LastPos;
	TransformComponent* m_pTransform = nullptr;
	float m_VectorRate = 0.0f;
	float m_VectorInterval = 0.2f;
	bool m_IsColliding = false;
	std::vector<Entity*> m_pWallColliders;
};

