#include "Walls.h"

#include "CollisionManager.h"
#include "TextureManager.h"

Walls::Walls(SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename)
	:mCollider(this, m_transform, pCollisionManager)
	,mpCollisionManager(pCollisionManager)
{
	mName = "Wall";
	mType = "Solidw";

	m_transform = dest;

	auto position_x = static_cast<float>(m_transform.x);
	auto position_y = static_cast<float>(m_transform.y);

	mCollider.SetTransForm(Vector2{ position_x, position_y }, Vector2<float>{ 32, 32 });
	m_pTexture = TextureManager::LoadTexture(filename);
	
}

Walls::~Walls()
{
	mpCollisionManager->RemoveActiveCollider(&mCollider);
}


void Walls::Renderer()
{
	mCollider.Render(SDL_Game::m_pRenderer);
}

void Walls::Update(double deltaTime)
{
	Tile::Update(deltaTime);
}

void Walls::OnCollision(Collider* pCollider)
{
	Tile::OnCollision(pCollider);
}
