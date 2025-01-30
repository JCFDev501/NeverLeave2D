#pragma once
#include "Tile.h"
class FairyFountain : public Tile
{
	Collider mCollider;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;
public:
	FairyFountain(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename);
	~FairyFountain();
	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;
};

