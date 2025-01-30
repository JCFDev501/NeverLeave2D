#pragma once
#include "Walls.h"


class GameState;

class Gates : public Walls
{
	GameState* m_pOwner;
public:
	Gates(GameState* pOwner, SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename);
	void Update(double deltaTime) override;

};

