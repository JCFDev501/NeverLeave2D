#pragma once
#include "Tile.h"

class Walls : public Tile 
{
	Collider mCollider;
	CollisionManager* mpCollisionManager;


public:
	Walls(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename);
	~Walls();
	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;
};
