#include "MiniginPCH.h"
#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	
	if ((recA.x + recA.w) < recB.x || (recB.x + recB.w) < recA.x)
	{
		return false;
	}

	// If one rectangle is under the other
	if (recA.y > (recB.y + recB.h) || recB.y > (recA.y + recA.h) )
	{
		return false;
	}

	return true;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.GetCollider(), colB.GetCollider()))
	{
		//std::cout << colA.m_Tag << " hit: " << colB.m_Tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}