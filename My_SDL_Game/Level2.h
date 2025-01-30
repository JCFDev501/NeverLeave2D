#pragma once
#include "DungeonCrawlerGame.h"
#include "GameState.h"
#include "Ghost.h"
#include "KeyboardAndMouse.h"
#include "PlayerCharacter.h"
class Level2 : public GameState
{
	// Pointer to the state machine running this state.
	DungeonCrawlerGame* m_pOwner;

	PlayerCharacter* mpPlayer;

	CollisionManager* mpCollisionManager;

	// Controller
	KeyboardAndMouse mController;

	// Storing all game objects in a vector
	std::list<GameObject*> mGameObjects;

	TTF_Font* m_pFont;

	int mEnemyKillCount = 0;
	int mMaxEnemy = 4;
	bool mDead = false;

	int mMaxnumberOfBats = 2;
	int mMaxnumberOfGhost = 2;

	bool mSaved = false;

public:
	Level2(DungeonCrawlerGame* pOwner, PlayerCharacter* pPlayer, CollisionManager* pCollisionManager, TTF_Font* pFont);
	~Level2() override;

	void Render() override;

	void Update(double deltaTime) override;

	bool HandleEvent(SDL_Event* pEvent) override;

	void Enter() override;

	bool Save();
};

