#pragma once
#include "BackGround.h"
#include "DungeonCrawlerGame.h"
#include "GameState.h"

class WinScreen : public GameState
{
	// Pointer to the state machine running this state.
	DungeonCrawlerGame* m_pOwner;

	// Storing all gam objects in a vector
	std::vector<GameObject*> mGameObjects;

public:
	WinScreen(DungeonCrawlerGame* pOwner, TTF_Font* pFont);
	~WinScreen() override;

	void Render() override;

	bool HandleEvent(SDL_Event* pEvent) override;
};

