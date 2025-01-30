#include "Chest.h"

#include "Bomb.h"
#include "Coins.h"
#include "CollisionManager.h"
#include "Key.h"
#include "ManaCrystal.h"
#include "RandomNumberGen.h"
#include "TextureManager.h"

Chest::Chest(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager)
	:mCollider(this, m_transform, pCollisionManager)
	,mOpened(false)
	,mLootCollected(false)
	,m_pCollisionManager(pCollisionManager)
	,m_pLoot(nullptr)
{
	mName = "Chest";
	mType = "Solid";

	m_transform = dest;

	auto position_x = static_cast<float>(m_transform.x);
	auto position_y = static_cast<float>(m_transform.y);

	mCollider.SetTransForm(Vector2{ position_x, position_y }, Vector2<float>{ 32, 32 });

	m_pTexture = TextureManager::LoadTexture("assets/Tiles/Chest.png");
}

Chest::~Chest()
{
}

void Chest::Renderer()
{
	mCollider.Render(SDL_Game::m_pRenderer);

	if (m_pLoot != nullptr && m_pLoot->GetActive())
		m_pLoot->Renderer();
}

void Chest::Update(double deltaTime)
{
	if (mOpened)
	{
		m_pTexture = TextureManager::LoadTexture("assets/Tiles/ChestOpened.png");
		mOpened = false;
		Reward();
		mLootCollected = true;
	}

	if (m_pLoot != nullptr && m_pLoot->GetActive())
		m_pLoot->Update(deltaTime);
}

void Chest::OnCollision(Collider* pCollider)
{
	if (!mOpened && !mLootCollected)
	{
		if (pCollider->GetOwner()->GetName() == "Player" && pCollider->GetOwner()->GetDirection().x == mUp.x
			&& pCollider->GetOwner()->GetDirection().y == mUp.y)
		{
			mOpened = true;
			m_pCollisionManager->RemoveActiveCollider(pCollider);
			mType = "Trigger";
		}
	}
	
}

void Chest::Reward()
{
	m_pLoot = nullptr;
	delete m_pLoot;

	RandomNumberGen lootManager(0, 3);

	const int randNumber = lootManager.GetRandomNumberInt();

	// If RandNum = 0 ....
	if (randNumber == 0)
	{
		m_pLoot = new Coins(SDL_Rect{ m_transform.x, m_transform.y - 32, 16, 16 }, m_pCollisionManager);
	}
	// If RandNum = 1..
	else if (randNumber == 1)
	{
		m_pLoot = new Bomb(SDL_Rect{ m_transform.x, m_transform.y - 32, 32, 32 }, m_pCollisionManager);
	}
	// If RandNum = 2..
	else if (randNumber == 2)
	{
		m_pLoot = new Key(SDL_Rect{ m_transform.x, m_transform.y - 32, 32, 32 }, m_pCollisionManager);
	}
	// If RandNum = 3..
	else if (randNumber == 3)
	{
		m_pLoot = new ManaCrystal(SDL_Rect{ m_transform.x, m_transform.y - 32, 32, 32 }, m_pCollisionManager);
	}
	
}

