#pragma once
#include "Animator.h"
#include "GameObject.h"
#include "Collider.h"

class Bomb : public GameObject
{
	Animator mSpin;
	Collider m_collider;

	int mPositionX;
	int mPositionY;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;

	SDL_Rect mBoxColider{ 16, 16, 16, 16 };
public:
	Bomb(SDL_Rect transform, CollisionManager* pCollisionManager);
	~Bomb() override;
	void Update(double deltaTime) override;
	void Renderer() override;
	void OnCollision(Collider* pCollider) override;
};

