#include "Door.h"

#include "TextureManager.h"

Door::Door(SDL_Rect transform, CollisionManager* pCollisionManager, Switch* pSwitch)
	:mCollider(this, m_transform, pCollisionManager)
	,m_pSwitch(pSwitch)
{
	mName = "Door";
	mPositionX = transform.x;
	mPositionY = transform.y;
	m_transform.x = transform.x;
	m_transform.y = transform.y;
	m_transform.w = transform.w;
	m_transform.h = transform.h;
	mSpeed = 0;

	//mCollider.SetTransForm(SDL_Rect{transform.x, transform.y, 64, 16});

	auto position_x = static_cast<float>(m_transform.x);
	auto position_y = static_cast<float>(m_transform.y);
	auto size_w = static_cast<float>(m_transform.w);
	auto size_h = static_cast<float>(m_transform.h);

	mCollider.SetTransForm(Vector2<float>{position_x, position_y}, Vector2<float>{size_w, size_h});

	m_pTexture = TextureManager::LoadTexture("assets/door.png");
}

Door::~Door()
{
	SDL_DestroyTexture(m_pTexture);
}

void Door::Renderer()
{
	TextureManager::Draw(m_pTexture, m_transform);
	mCollider.Render(SDL_Game::m_pRenderer);
}

void Door::Update(double deltaTime)
{
	auto position_x = static_cast<float>(m_transform.x);
	auto position_y = static_cast<float>(m_transform.y);

	if (m_pSwitch->GetFlipped())
	{
		if (!mOpened)
		{
			mCollider.SetTransForm(Vector2<float>{ position_x, position_y}, Vector2<float>{ 64, 8});
		
			m_pTexture = TextureManager::LoadTexture("assets/door2.png");
			mOpened = true;
		}
	}
}

void Door::OnCollision(Collider* pCollider)
{
	if (m_pSwitch->GetFlipped())
	{
		mPassed = true;
	}
}
