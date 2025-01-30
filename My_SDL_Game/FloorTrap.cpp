#include "FloorTrap.h"

#include "TextureManager.h"

FloorTrap::FloorTrap(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename)
	:mCollider(this, m_transform, pCollisionManager)
{
	mName = "SpikedFloor";
	mType = "Trigger";

	m_transform = dest;

	auto position_x = static_cast<float>(m_transform.x);
	auto position_y = static_cast<float>(m_transform.y);

	mCollider.SetTransForm(Vector2<float>{ position_x + 10, position_y}, Vector2<float>{ 7, 7});

	m_pTexture = TextureManager::LoadTexture(filename);
}

void FloorTrap::Renderer()
{
	mCollider.Render(SDL_Game::m_pRenderer);
}

void FloorTrap::Update(double deltaTime)
{
	Tile::Update(deltaTime);
}

void FloorTrap::OnCollision(Collider* pCollider)
{
	Tile::OnCollision(pCollider);
}
