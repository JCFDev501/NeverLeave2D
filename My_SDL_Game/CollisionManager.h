#pragma once
#include <string>
#include <vector>


class Collider;

// Maintains a List of all colliders and checks their collision
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	// All currently active collider
	std::vector<Collider*> m_activeColliders;

	// Register a new collider
	void AddActiveCollider(Collider* pCollider);

	// Un-register a collider.
	void RemoveActiveCollider(Collider* pCollider);

	// Find all colliders that overlap and notify of any collision
	// Returns whether or not collision occurred.
	std::string CheckForCollisionAndNotify(Collider* pColliderToCheck);
};

