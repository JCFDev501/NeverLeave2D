#pragma once
#include "Animator.h"
#include "GameObject.h"
#include "Collider.h"

class Key : public GameObject
{
	Animator mSpin;
	Collider m_collider;

	int mPositionX;
	int mPositionY;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;

public:
	Key(SDL_Rect transform, CollisionManager* pCollisionManager);
	~Key() override;
	void Update(double deltaTime) override;
	void Renderer() override;
	void OnCollision(Collider* pCollider) override;
};

