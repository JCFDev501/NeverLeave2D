#pragma once
#include "DungeonCrawlerGame.h"
#include "GameState.h"
#include <SDL_mixer.h>


// Game state representing the main menu.
class MainMenu : public GameState 
{
	// Pointer to the state machine running this state.
	DungeonCrawlerGame* m_pOwner;

	// Storing all gam objects in a vector
	std::vector<GameObject*> mGameObjects;

	int NumberofClicksOnPlay = 0;
	
public:
	MainMenu(DungeonCrawlerGame* pOwner, TTF_Font* pFont);
	~MainMenu() override;

	void Render() override;
	bool HandleEvent(SDL_Event* pEvent) override;
};

