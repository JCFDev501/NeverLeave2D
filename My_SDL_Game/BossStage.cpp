#include "BossStage.h"

#include <iostream>

#include "BackGround.h"
#include "Bat.h"
#include "DumbGhost.h"
#include "GuardZombie.h"
#include "Ui.h"
#include "UITextField.h"

BossStage::BossStage(DungeonCrawlerGame* pOwner, PlayerCharacter* pPlayer, CollisionManager* pCollisionManager, TTF_Font* pFont)
	:m_pOwner(pOwner)
	,mpPlayer(pPlayer)
	,mpCollisionManager(pCollisionManager)
{

	mpCollisionManager->m_activeColliders.clear();

	// Map
	mGameObjects.push_back(new TileMap(this ,pCollisionManager, "assets/Levels/RoomTemplet.txt"));

	
	mGameObjects.push_back(mpPlayer);

	// BatBoss
	mpBat = new Bat(Vector2<float>{410, 279}, Vector2<float>{80, 80}, mpPlayer, pCollisionManager);
	mGameObjects.push_back(mpBat);

	////BatBaby
	mGameObjects.push_back(new GuardZombie(Vector2<float>{64, 64}, Vector2<float>{16, 16}, mpPlayer, pCollisionManager, 70));
	mGameObjects.push_back(new GuardZombie(Vector2<float>{32 * 15, 64}, Vector2<float>{20, 20}, mpPlayer, pCollisionManager, 80));
	mGameObjects.push_back(new GuardZombie(Vector2<float>{32 * 20, 64}, Vector2<float>{20, 20}, mpPlayer, pCollisionManager, 90));
	mGameObjects.push_back(new GuardZombie(Vector2<float>{32 * 22, 64}, Vector2<float>{20, 20}, mpPlayer, pCollisionManager, 100));

	//UI
	mGameObjects.push_back(new	Ui(SDL_Rect{ 0,0, 32 * 30, 32 * 3 }, SDL_Game::m_pRenderer, mpPlayer, pFont));
}

BossStage::~BossStage()
{
	for (const auto& mGameObject : mGameObjects)
	{
		delete mGameObject;
	}
}

void BossStage::Render()
{
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(SDL_Game::m_pRenderer);

	// Render GameObjects
	for (const auto& mGameObject : mGameObjects)
	{
		mGameObject->Renderer();
	}
}

void BossStage::Update(double deltaTime)
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
		if (toDelete->GetName() == "ZombieGuard")
		{
 			int health = mpBat->GetHealth() - 50;
			mpBat->SetHealth(health);
		}
			
	}
	
	
	
	mGameObjects.remove(toDelete);

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

void BossStage::Enter()
{
	mpPlayer->setX(32 * 14);
	mpPlayer->setY(32 * 14);
}

bool BossStage::HandleEvent(SDL_Event* pEvent)
{
	bool quit = mController.KeyboardAndMouseInputHandler(mpPlayer, pEvent, m_pOwner);

	if (quit)
	{
		return true;
	}

	if (mpBat->GetHealth() == 0)
	{
		m_pOwner->LoadScene(DungeonCrawlerGame::WinState);
	}

	return false;
}
