#include "CollisionManager.h"
#include <SDL.h>

#include "Collider.h"
#include "GameObject.h"
CollisionManager::CollisionManager()
= default;

CollisionManager::~CollisionManager()
= default;

// Register a new collider
void CollisionManager::AddActiveCollider(Collider* pCollider)
{
	// Make sure it's not already present.
	if (std::find(m_activeColliders.begin(), m_activeColliders.end(), pCollider) == m_activeColliders.end())
	{
		// if its not already present add it to the vector
		m_activeColliders.push_back(pCollider);
	}
	
}

// Un-register a collider.
void CollisionManager::RemoveActiveCollider(Collider* pCollider)
{
	// Find the collider
	auto location = std::find(m_activeColliders.begin(), m_activeColliders.end(), pCollider);

	// if it's found, erase it from the vector
	if (location != m_activeColliders.end())
	{
		m_activeColliders.erase(location);
	}
}

// Find all colliders that overlap and notify of any collision
// Returns whether or not collision occurred.
std::string CollisionManager::CheckForCollisionAndNotify(Collider* pColliderToCheck)
{
	using Vector2 = Vector2<float>;

	// Allocate a boolean for whether any collision have occurred.
	bool didCollide = false;

	// Get pColliderToCheck's transform.
	Vector2 colliderPosition = pColliderToCheck->GetPosition();
	Vector2 colliderSize = pColliderToCheck->GetSize();

	// Calculate bounds.
	float left = colliderPosition.m_x;
	float right = left + colliderSize.m_x;
	float top = colliderPosition.m_y;
	float bottom = top + colliderSize.m_y;

	std::string dummy;

	// check against every active collider.
	for(Collider* pOtherCollider : m_activeColliders)
	{
		// Make sure we don't check a Collider vs. itself.
		if (pColliderToCheck == pOtherCollider)
			continue;

		// Get the other colliders transform.
		Vector2 otherColliderPosition = pOtherCollider->GetPosition();
		Vector2 otherColliderSize = pOtherCollider->GetSize();

		// Calculate the bounds of the other collider.
		float otherLeft = otherColliderPosition.m_x;
		float otherRight = otherLeft + otherColliderSize.m_x;
		float otherTop = otherColliderPosition.m_y;
		float otherBottom = otherTop + otherColliderSize.m_y;

		// Check if they overLap horizontally.
		bool xOverlap = left < otherRight && right > otherLeft;

		// Check if they overLap Vertically.
		bool yOverlap = top < otherBottom && bottom > otherTop;

		// if both x and y are true, they collide.
		if(xOverlap && yOverlap)
		{
			// A collision has occurred.
			dummy = pOtherCollider->GetOwner()->GetType();

			// Notify both colliders ownwers of the collision.
			pColliderToCheck->GetOwner()->OnCollision(pOtherCollider); // notify object A
			pOtherCollider->GetOwner()->OnCollision(pColliderToCheck);         // notify  object B
		}
	}

	// Return whether any collisions occurred

	return dummy;
}
