#pragma once
#include "DungeonCrawlerGame.h"
#include "GameState.h"
#include "Ghost.h"
#include "KeyboardAndMouse.h"
#include "PlayerCharacter.h"

class Tutorial : public GameState
{
protected:

	// Pointer to the state machine running this state.
	DungeonCrawlerGame* m_pOwner;

	PlayerCharacter* mpPlayer;

	TileMap* mpTileMap;

	CollisionManager* mpCollisionManager;

	// Controller
	KeyboardAndMouse mController;

	// Storing all game objects in a vector
	std::list<GameObject*> mGameObjects;

	TTF_Font* m_pFont;

	int mEnemyKillCount = 0;
	int mMaxEnemy = 4;
	bool mDead = false;

	int mMaxnumberOfCoins = 6;
	int mMaxnumberOfBats = 1;
	int mMaxnumberOfGhost = 3;

	bool mSaved = false;
	
public:
	Tutorial(DungeonCrawlerGame* pOwner, PlayerCharacter* pPlayer, CollisionManager* pCollisionManager, TTF_Font* pFont);
	~Tutorial() override;

	void Render() override;

	void Update(double deltaTime) override;

	bool HandleEvent(SDL_Event* pEvent) override;

	void Enter() override;

	bool Save();
};

