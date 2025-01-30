#pragma once
#include <SDL.h>
#include <string>

#include "Vector2.h"
class CollisionManager;
class GameObject;

// An anti-aligned bounding box (AABB) collider.
class Collider
{
	using Vector2 = Vector2<float>;

	// Pointer to gameObject that owns this collider.
	GameObject* m_pOwner;

	// Position and dimensions
	Vector2 m_position;
	Vector2 m_size;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;
public:
	Collider(GameObject* pOwner, SDL_Rect transform, CollisionManager* pCollisionManager);
	~Collider();

	// Returns pointer to this collider's owner
	GameObject* GetOwner() const { return m_pOwner; }

	// Return position and dimensions
	Vector2 GetPosition() { return m_position; }
	Vector2 GetSize() { return m_size; }
	void SetTransForm(Vector2 position, Vector2 size) { m_position = position; m_size = size; }

	// Updates position
	void SetPosition(Vector2 newPosition);

	// Attempts to move by the given amount.
	// Returns whether the collision was successful
	std::string TryMove(Vector2 deltaPosition);

	void Render(SDL_Renderer* pRenderer) const;
};

