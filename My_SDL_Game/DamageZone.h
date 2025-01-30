#pragma once

#include "Collider.h"
#include "GameObject.h"
class DamageZone : public GameObject
{
	int mPositionX;
	int mPositionY;
	// collider component for checking
	Collider m_collider;
	SDL_Rect mBoxColider{ 32, 32, 32, 32 };
public:
	DamageZone(SDL_Rect transform, CollisionManager* pCollisionManager);
	~DamageZone();
	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;
};

