#include "Collider.h"

#include <iostream>

#include "CollisionManager.h"

Collider::Collider(GameObject* pOwner, SDL_Rect transform, CollisionManager* pCollisionManager)
	:m_pOwner(pOwner)
	,m_position{static_cast<float>(transform.x), static_cast<float>(transform.y)}
	,m_size{ static_cast<float>(transform.w), static_cast<float>(transform.h) }
	,m_pCollisionManager(pCollisionManager)
{
	if (pCollisionManager != nullptr)
	{
		pCollisionManager->AddActiveCollider(this);
	}
}

Collider::~Collider()
{
	if (m_pCollisionManager != nullptr)
	{
		m_pCollisionManager->RemoveActiveCollider(this);
	}
}

// Updates position
void Collider::SetPosition(Vector2 newPosition)
{
	m_position = newPosition;
}

// Attempts to move by the given amount.
// Returns whether the collision was successful
std::string Collider::TryMove(Vector2 deltaPosition)
{
	// Make sure there is a manager assigned.
	if (m_pCollisionManager == nullptr)
	{
		std::string error = "Warning: Collider is not assigned a referee.";
		return error;
	}

	// Temporarily update the collider's position.
	m_position.m_x += deltaPosition.m_x;
	m_position.m_y += deltaPosition.m_y;

	// Perform the collision check.
	std::string didCollide = m_pCollisionManager->CheckForCollisionAndNotify(this);

	// If the move was invalid undo it
	if (didCollide.empty() || didCollide == "Trigger")
	{
		return didCollide;
	}
	

	m_position.m_x -= deltaPosition.m_x;
	m_position.m_y -= deltaPosition.m_y;
	

	// Return whether the move was successful.
	return didCollide;
}

void Collider::Render(SDL_Renderer* pRenderer) const
{
	int transform_x = static_cast<int>(m_position.m_x);
	int transform_y = static_cast<int>(m_position.m_y);
	int transform_w = static_cast<int>(m_size.m_x);
	int transform_h = static_cast<int>(m_size.m_y);

	SDL_Rect transform{ transform_x, transform_y, transform_w, transform_h };
	// IF YOU WANT TO SEE ACTUAL BOX COLLIDERS UNCOMMENT THIS...
	//SDL_SetRenderDrawColor(pRenderer,255, 0, 0, SDL_ALPHA_OPAQUE);
	//SDL_RenderDrawRect(pRenderer, &transform);
}

