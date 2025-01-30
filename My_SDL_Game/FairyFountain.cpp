#include "FairyFountain.h"

#include "CollisionManager.h"
#include "TextureManager.h"

FairyFountain::FairyFountain(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename)
	:mCollider(this, m_transform, pCollisionManager)
	,m_pCollisionManager(pCollisionManager)
{
	mName = "FairyFountain";
	mType = "Trigger";

	m_transform = dest;

	auto position_x = static_cast<float>(m_transform.x);
	auto position_y = static_cast<float>(m_transform.y);

	mCollider.SetTransForm(Vector2<float>{ position_x + 10, position_y}, Vector2<float>{ 7, 7});
	m_pTexture = TextureManager::LoadTexture(filename);
}

FairyFountain::~FairyFountain()
{
	//m_pCollisionManager->RemoveActiveCollider(&mCollider);
}

void FairyFountain::Renderer()
{
	mCollider.Render(SDL_Game::m_pRenderer);
}

void FairyFountain::Update(double deltaTime)
{
	Tile::Update(deltaTime);
}

void FairyFountain::OnCollision(Collider* pCollider)
{
	Tile::OnCollision(pCollider);
}
