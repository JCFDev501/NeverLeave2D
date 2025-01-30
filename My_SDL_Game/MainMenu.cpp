#include "MainMenu.h"

#include <iostream>

#include "BackGround.h"
#include "PlayButton.h"
#include "QuitButton.h"
#include "UITextField.h"


MainMenu::MainMenu(DungeonCrawlerGame* pOwner, TTF_Font* pFont)
	:m_pOwner(pOwner)
	,mGameObjects()
{
	// Main Menu BackGround
	mGameObjects.push_back(new BackGround(SDL_Rect{ 0, 0, 960, 608 }, "assets/Main Menu Background.png", SDL_Game::m_pRenderer));

	// Text Field Displaying Title
	mGameObjects.push_back(new UITextField(pFont, "Never Leave", SDL_Color{ 100,0,0, SDL_ALPHA_OPAQUE },
		Vector2{ 32 * 9 + 1, 32 * 4 }, SDL_Game::m_pRenderer));

	// Text Field Displaying Title
	mGameObjects.push_back(new UITextField(pFont, "By Jaylin Ferrell", SDL_Color{ 0,0,0, SDL_ALPHA_OPAQUE },
		Vector2{ 32 * 4 + 1, 32 * 19 + 10 }, SDL_Game::m_pRenderer));

	// Button to start the game.
	auto pPlayButton = new PlayButton(SDL_Rect{ 32 * 11 + 1, 32 * 9 + 14, 300, 75 }, SDL_Game::m_pRenderer);

	// Lambdas []()type
	pPlayButton->SetCallBack([pOwner]()->void
	{
		if (pOwner->Init())
			pOwner->LoadScene(DungeonCrawlerGame::TutorialScreen);
	});

	mGameObjects.push_back(pPlayButton);

	// Button to start the game.
	auto pLoad = new PlayButton(SDL_Rect{ 32 * 5 + 1, 32 * 12 + 14, 100, 75 }, SDL_Game::m_pRenderer);

	// Lambdas []()type
	pLoad->SetCallBack([pOwner]()->void
	{
		pOwner->GetSave()->Load();

		if(pOwner->GetSave()->GetState() == 1)
		{
			if (pOwner->Init())
				pOwner->LoadScene(DungeonCrawlerGame::TutorialScreen);
		}
		else if (pOwner->GetSave()->GetState() == 2)
		{
			if (pOwner->Init())
				pOwner->LoadScene(DungeonCrawlerGame::Room1Screen);
		}
		else if (pOwner->GetSave()->GetState() == 3)
		{
			if (pOwner->Init())
				pOwner->LoadScene(DungeonCrawlerGame::Room2Screen);
		}
		else if (pOwner->GetSave()->GetState() == 4)
		{
			if (pOwner->Init())
				pOwner->LoadScene(DungeonCrawlerGame::Room3Screen);
		}
		
	});

	mGameObjects.push_back(pLoad);

	// Button to start the game.
	auto pQuitButton = new QuitButton(SDL_Rect{ 32 * 11 + 1, 32 * 12, 300, 75 }, SDL_Game::m_pRenderer);

	pQuitButton->SetCallBack([pOwner]()->void
	{
		pOwner->GetGame()->Quit();
	});

	mGameObjects.push_back(pQuitButton);

}

MainMenu::~MainMenu()
{
	for (const auto& mGameObject : mGameObjects)
	{
		delete mGameObject;
	}

	
}

void MainMenu::Render()
{
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDL_Game::m_pRenderer);
	for (const auto& mGameObject : mGameObjects)
	{
		mGameObject->Renderer();
	}
	SDL_RenderPresent(SDL_Game::m_pRenderer);
}

bool MainMenu::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
		// determine actions based on event type.
	case SDL_WINDOWEVENT:
		// Close window to quit
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
			return true;
		break;
		
	}

	for (const auto& mGameObject : mGameObjects)
	{
		if (mGameObjects.empty())
		{
			break;
		}

		mGameObject->HandleEvent(pEvent);
	}
	
	

	return false;
}
