#include "WinScreen.h"
#include "LoseScreen.h"

#include "MenuButton.h"
#include "QuitButton.h"
#include "RestartButton.h"
#include "UITextField.h"

WinScreen::WinScreen(DungeonCrawlerGame* pOwner, TTF_Font* pFont)
	:m_pOwner(pOwner)
{
	// Main Menu BackGround
	mGameObjects.push_back(new BackGround(SDL_Rect{ 0, 0, 960, 800 }, "assets/WinBackGround.png", SDL_Game::m_pRenderer));

	// Text Field Displaying Title
	mGameObjects.push_back(new UITextField(pFont, "You Will Never Leave", SDL_Color{ 0,0,0, SDL_ALPHA_OPAQUE },
		Vector2{ 32 * 5 + 1, 32 * 7 }, SDL_Game::m_pRenderer));

	// Button to Quit the game.
	auto pQuitButton = new QuitButton(SDL_Rect{ 32 * 7 + 1, 32, 300, 75 }, SDL_Game::m_pRenderer);

	pQuitButton->SetCallBack([pOwner]()->void
	{
		pOwner->GetGame()->Quit();
	});

	mGameObjects.push_back(pQuitButton);

	// Button to Restart Game.
	auto pRestartButton = new RestartButton(SDL_Rect{ 32, 32, 64, 75 }, SDL_Game::m_pRenderer);

	pRestartButton->SetCallBack([pOwner]()->void
	{
		if (pOwner->Init())
			pOwner->LoadScene(DungeonCrawlerGame::TutorialScreen);
	});

	mGameObjects.push_back(pRestartButton);

	// Button to Menu.
	auto pMenuButton = new MenuButton(SDL_Rect{ 32 * 20, 32, 300, 75 }, SDL_Game::m_pRenderer);

	pMenuButton->SetCallBack([pOwner]()->void
	{
		pOwner->LoadScene(DungeonCrawlerGame::Menu);
	});

	mGameObjects.push_back(pMenuButton);
}

WinScreen::~WinScreen()
{
	// Handle GameObject Events
	for (const auto& mGameObject : mGameObjects)
	{
		delete mGameObject;
	}
}

void WinScreen::Render()
{
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDL_Game::m_pRenderer);
	for (const auto& mGameObject : mGameObjects)
	{
		mGameObject->Renderer();
	}
	SDL_RenderPresent(SDL_Game::m_pRenderer);
}

bool WinScreen::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
		// determine actions based on event type.
	case SDL_WINDOWEVENT:
		// Close window to quit
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
		{
			return true;
		}
		break;
	}

	// Handle GameObject Events
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