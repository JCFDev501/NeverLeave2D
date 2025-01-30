#include "Level5.h"
#include "DumbGhost.h"
#include "GuardZombie.h"
#include "Ui.h"

Level5::Level5(DungeonCrawlerGame* pOwner, PlayerCharacter* pPlayer, CollisionManager* pCollisionManager,
	TTF_Font* pFont)
	:m_pOwner(pOwner)
	, mpPlayer(pPlayer)
	, mpCollisionManager(pCollisionManager)
{
	// Map
	mGameObjects.push_back(new TileMap(this, pCollisionManager, "assets/Levels/Room5.txt"));

	// Player
	mGameObjects.push_back(mpPlayer);

	// Particle
	mGameObjects.push_back(new ParticleSystem(Vector2<float>{32 * 8, 32 * 10}, 32, 20, 25,
		255, 255, 2, 255, Vector2<int>{2, 2}));

	mGameObjects.push_back(new ParticleSystem(Vector2<float>{32 * 23, 32 * 13}, 64, 30, 25,
		255, 0, 255, 255, Vector2<int>{3, 3}));

	//UI
	mGameObjects.push_back(new Ui(SDL_Rect{ 0,0, 32 * 30, 32 * 3 }, SDL_Game::m_pRenderer, mpPlayer, pFont));

}

Level5::~Level5()
{
	for (const auto& mGameObject : mGameObjects)
	{
		if (mGameObject->GetName() != "Player")
			delete mGameObject;
	}
}

void Level5::Enter()
{
	mpPlayer->SetPassGate(true);
	mpPlayer->SetWentThroughGate(false);
	mpPlayer->setX(32 * 14);
	mpPlayer->setY(32 * 14);
}

void Level5::Update(double deltaTime)
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
	{
		if (toDelete->GetName() == "ZombieGuard" || toDelete->GetName() == "DumbGhost")
		{
			mGameObjects.remove(toDelete);
			mEnemyKillCount++;
			delete toDelete;
			toDelete = nullptr;


		}

	}

	if (toDelete != nullptr)
		mGameObjects.remove(toDelete);

	if (mEnemyKillCount == mMaxEnemy)
	{
		mStateCleared = true;
		mpPlayer->SetPassGate(true);
	}

	if (mpPlayer->GetWentThroughGate())
	{
		m_pOwner->LoadScene(DungeonCrawlerGame::BossStageScreen);
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

bool Level5::HandleEvent(SDL_Event* pEvent)
{
	bool quit = mController.KeyboardAndMouseInputHandler(mpPlayer, pEvent, m_pOwner);

	if (quit)
	{
		return true;
	}

	return false;
}

void Level5::Render()
{
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDL_Game::m_pRenderer);

	//Render GameObjects
	for (const auto& mGameObject : mGameObjects)
	{
		mGameObject->Renderer();
	}
}