#include "WinZone.h"

#include "SDL_Game.h"

WinZone::WinZone(SDL_Rect transform, CollisionManager* pCollisionManager)
	:m_collider(this, mBoxColider, pCollisionManager)
{
	mName = "WinZone";
	mType = "Trigger";
	mPositionX = transform.x;
	mPositionY = transform.y;
	m_transform.x = transform.x;
	m_transform.y = transform.y;
	m_transform.w = transform.w;
	m_transform.h = transform.h;
	mSpeed = 0;

	auto position_x = static_cast<float>(m_transform.x);
	auto position_y = static_cast<float>(m_transform.y);
	auto size_w = static_cast<float>(m_transform.w);
	auto size_h = static_cast<float>(m_transform.h);

	m_collider.SetTransForm(Vector2{ position_x, position_y }, Vector2{ size_w, size_h });
}

WinZone::~WinZone()
= default;

void WinZone::Renderer()
{
	m_collider.Render(SDL_Game::m_pRenderer);
}

void WinZone::Update(double deltaTime)
{
	// tbd
}

void WinZone::OnCollision(Collider* pCollider)
{
}
