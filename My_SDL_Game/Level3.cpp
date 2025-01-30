#include "Level3.h"

#include <iostream>

#include "DumbGhost.h"
#include "GuardZombie.h"
#include "Ui.h"

Level3::Level3(DungeonCrawlerGame* pOwner, PlayerCharacter* pPlayer, CollisionManager* pCollisionManager,
	TTF_Font* pFont)
	:m_pOwner(pOwner)
	, mpPlayer(pPlayer)
	, mpCollisionManager(pCollisionManager)
	, m_pFont(pFont)
{
	mpCollisionManager->m_activeColliders.clear();

	mpPlayer->SetPassGate(false);
	mpPlayer->SetWentThroughGate(false);
	mpPlayer->setX(32 * 14);
	mpPlayer->setY(32 * 14);

	mCurrentState = 4;
}

Level3::~Level3()
{
	for (const auto& mGameObject : mGameObjects)
	{
		if (mGameObject->GetName() != "Player")
			delete mGameObject;
	}
}

void Level3::Enter()
{
	// Get the Save data reference
	SaveData* pSave = m_pOwner->GetSave();
	SaveData::Data& data = pSave->GetData();


	// Check if has been loaded
	if (!pSave->GetIsLoaded())
	{
		// Map
		mGameObjects.push_back(new TileMap(this, mpCollisionManager, "assets/Levels/Room3.txt"));

		data.mStateCleared = mStateCleared;
		data.mState = mCurrentState;

		// Player
		mGameObjects.push_back(mpPlayer);

		data.mPlayerPosition.m_x = mpPlayer->GetX();
		data.mPlayerPosition.m_y = mpPlayer->GetY();
		data.mPlayerBombs = mpPlayer->GetBombs();
		data.mPlayerGold = mpPlayer->GetGold();
		data.mPlayerHealth = mpPlayer->GetHealth();
		data.mPlayerKeys = mpPlayer->GetKeys();
		data.mPlayerMana = mpPlayer->GetMana();
		data.mPlayerCanPass = mpPlayer->GetPassGate();

		//BatBaby
		data.mNumberOfBats = mMaxnumberOfBats;

		// Ghost
		data.mNumberOfGhost = mMaxnumberOfGhost;

	}

	if (data.mState != 4)
	{
		// Map
		mGameObjects.push_back(new TileMap(this, mpCollisionManager, "assets/Levels/Room3.txt"));

		data.mStateCleared = mStateCleared;
		data.mState = mCurrentState;

		// Player
		mGameObjects.push_back(mpPlayer);

		data.mPlayerPosition.m_x = mpPlayer->GetX();
		data.mPlayerPosition.m_y = mpPlayer->GetY();
		data.mPlayerBombs = mpPlayer->GetBombs();
		data.mPlayerGold = mpPlayer->GetGold();
		data.mPlayerHealth = mpPlayer->GetHealth();
		data.mPlayerKeys = mpPlayer->GetKeys();
		data.mPlayerMana = mpPlayer->GetMana();
		data.mPlayerCanPass = mpPlayer->GetPassGate();

		//BatBaby
		data.mNumberOfBats = mMaxnumberOfBats;

		// Ghost
		data.mNumberOfGhost = mMaxnumberOfGhost;

	}




	mGameObjects.clear();

	// Map
	mGameObjects.push_back(new TileMap(this, mpCollisionManager, "assets/Levels/Room3.txt"));

	mStateCleared = data.mStateCleared;

	mCurrentState = data.mState;

	// Player
	mGameObjects.push_back(mpPlayer);
	mpPlayer->setX(data.mPlayerPosition.m_x);
	mpPlayer->setY(data.mPlayerPosition.m_y);
	mpPlayer->SetHealth(data.mPlayerHealth);
	mpPlayer->SetMana(data.mPlayerMana);
	mpPlayer->SetBombs(data.mPlayerBombs);
	mpPlayer->SetGold(data.mPlayerGold);
	mpPlayer->SetKeys(data.mPlayerKeys);
	mpPlayer->SetPassGate(data.mPlayerCanPass);

	//BatBaby
	float speed1 = 20;
	for (int i = 0; i < data.mNumberOfBats; i++)
	{
		mGameObjects.push_back(new GuardZombie(Vector2<float>{64 * 10, 32 * 11}, Vector2<float>{16, 16}, mpPlayer, mpCollisionManager, speed1));
		speed1 += 15;
	}

	// Ghost
	float speed2 = 30;
	for (int i = 0; i < data.mNumberOfGhost; i++)
	{
		mGameObjects.push_back(new DumbGhost(Vector2<float>{32 * 23, 300}, Vector2<float>{32, 32}, mpPlayer, mpCollisionManager, speed2));
		speed2 += 20;
	}

	// Particle
	mGameObjects.push_back(new ParticleSystem(Vector2<float>{32 * 8, 32 * 10}, 32, 20, 25,
		255, 255, 2, 255, Vector2<int>{2, 2}));

	mGameObjects.push_back(new ParticleSystem(Vector2<float>{32 * 23, 32 * 13}, 64, 30, 25,
		255, 0, 255, 255, Vector2<int>{3, 3}));

	//UI
	mGameObjects.push_back(new	Ui(SDL_Rect{ 0,0, 32 * 30, 32 * 3 }, SDL_Game::m_pRenderer, mpPlayer, m_pFont));


}

bool Level3::Save()
{
	// Get data ref
	SaveData* pSave = m_pOwner->GetSave();
	SaveData::Data& saveData = pSave->GetData();

	// update the values that we want to Save

	// Level data
	saveData.mStateCleared = mStateCleared;
	saveData.mState = mCurrentState;

	// Player data
	saveData.mPlayerPosition.m_x = mpPlayer->GetX();
	saveData.mPlayerPosition.m_y = mpPlayer->GetY();
	saveData.mPlayerHealth = mpPlayer->GetHealth();
	saveData.mPlayerBombs = mpPlayer->GetBombs();
	saveData.mPlayerMana = mpPlayer->GetMana();
	saveData.mPlayerGold = mpPlayer->GetGold();
	saveData.mPlayerKeys = mpPlayer->GetKeys();
	saveData.mPlayerCanPass = mpPlayer->GetPassGate();

	// Bats data
	saveData.mNumberOfBats = mMaxnumberOfBats;

	// Ghost data
	saveData.mNumberOfGhost = mMaxnumberOfGhost;

	// Time
	saveData.mTime.mSec = m_pOwner->GetSec();
	saveData.mTime.mMin = m_pOwner->GetMin();
	saveData.mTime.mHour = m_pOwner->GetHour();

	// perform Save
	return pSave->Save();
}

void Level3::Update(double deltaTime)
{
	GameState::Update(deltaTime);

	GameObject* toDelete = nullptr;

	// Update GameObjects4
	for (const auto& mGameObject : mGameObjects)
	{
		if (mGameObjects.empty())
			break;

		if (mGameObject != nullptr)
			mGameObject->Update(deltaTime);

		if (!mGameObject->GetActive())
			toDelete = mGameObject;
	}

	if (toDelete != nullptr)
		mGameObjects.remove(toDelete);

	if (toDelete != nullptr)
	{
		if (toDelete->GetName() == "ZombieGuard")
		{
			mEnemyKillCount++;
			mMaxnumberOfBats--;
			delete toDelete;
			toDelete = nullptr;
		}
		else if (toDelete->GetName() == "DumbGhost")
		{
			mEnemyKillCount++;
			mMaxnumberOfGhost--;
			delete toDelete;
			toDelete = nullptr;
		}

	}

	

	if (mEnemyKillCount == mMaxEnemy)
	{
		mStateCleared = true;
		mpPlayer->SetPassGate(true);

		if (!mSaved)
		{
			bool success = Save();

			if (success)
			{
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "Level Cleared and Save was successfully." << std::endl;
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "\n";
				mSaved = true;
			}
			else
			{
				std::cout << "Level Cleared, but Save was unsuccessfully." << std::endl;
			}

		}
	}

	if (mpPlayer->GetWentThroughGate())
	{
		m_pOwner->LoadScene(DungeonCrawlerGame::Room4Screen);
	}

	if (mStateCleared == false)
	{
		if (mpPlayer->GetHealth() == 0)
		{
			mDead = true;
			if (mDead)
			{
				mDead = false;
				m_pOwner->LoadScene(DungeonCrawlerGame::LoseState);
			}

		}
	}
}

bool Level3::HandleEvent(SDL_Event* pEvent)
{
	int quit = mController.KeyboardAndMouseInputHandler(mpPlayer, pEvent, m_pOwner);

	if (quit == 1)
	{
		return true;
	}

	return false;
}

void Level3::Render()
{
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDL_Game::m_pRenderer);

	//Render GameObjects
	for (const auto& mGameObject : mGameObjects)
	{
		mGameObject->Renderer();
	}
}