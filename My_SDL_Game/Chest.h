#pragma once
#include "Tile.h"

class Chest : public Tile
{
	Collider mCollider;
	bool mOpened;
	bool mLootCollected;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;

	GameObject* m_pLoot;
public:
	Chest(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager);
	~Chest();

	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;

private:
	void Reward();
};


