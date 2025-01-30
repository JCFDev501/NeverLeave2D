#pragma once
#include "Tile.h"

class FloorTrap : public Tile
{
	Collider mCollider;
public:
	FloorTrap(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename);
	~FloorTrap() = default;
	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;
};

