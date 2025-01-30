#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

#include "Tile.h"


class GameState;

class TileMap : public GameObject
{
	SDL_Rect mSrc;
	SDL_Rect mDest;

	Tile* m_pTile;
	CollisionManager* m_pCollisionManager;

	GameState* m_pOwner;

	// 2d Array

	Tile* mMap[16][30];
	int mLevel[16][30];

	int skip = 0;

	void create_map(std::string levelFileName);
	void load_map(CollisionManager* pCollisionManager, int alevel[16][30]);

public:
	TileMap(GameState* pOwner, CollisionManager* pCollisionManager, std::string levelFileName);
	~TileMap();

	
	void Renderer() override;

	void Update(double deltaTime) override;
};

