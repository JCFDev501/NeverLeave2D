#include "DamageZone.h"

#include "SDL_Game.h"

DamageZone::DamageZone(SDL_Rect transform, CollisionManager* pCollisionManager)
	:m_collider(this, mBoxColider, pCollisionManager)
{
	mName = "DamageZone";
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

	m_collider.SetTransForm(Vector2{position_x, position_y}, Vector2{size_w, size_h});

}

DamageZone::~DamageZone()
= default;

void DamageZone::Renderer()
{
	m_collider.Render(SDL_Game::m_pRenderer);
}

void DamageZone::Update(double deltaTime)
{
}

void DamageZone::OnCollision(Collider* pCollider)
{
}
