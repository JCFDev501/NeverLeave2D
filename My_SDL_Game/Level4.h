#pragma once

#include "DungeonCrawlerGame.h"
#include "GameState.h"
#include "Ghost.h"
#include "KeyboardAndMouse.h"
#include "PlayerCharacter.h"

class Level4 : public GameState
{
	// Pointer to the state machine running this state.
	DungeonCrawlerGame* m_pOwner;

	PlayerCharacter* mpPlayer;

	CollisionManager* mpCollisionManager;

	// Controller
	KeyboardAndMouse mController;

	// Storing all game objects in a vector
	std::list<GameObject*> mGameObjects;

	int mEnemyKillCount = 0;
	int mMaxEnemy = 4;
	bool mDead = false;

public:
	Level4(DungeonCrawlerGame* pOwner, PlayerCharacter* pPlayer, CollisionManager* pCollisionManager, TTF_Font* pFont);
	~Level4() override;

	void Render() override;

	void Update(double deltaTime) override;

	bool HandleEvent(SDL_Event* pEvent) override;

	void Enter() override;
};

