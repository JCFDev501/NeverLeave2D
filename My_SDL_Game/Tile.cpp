#include "Tile.h"

#include "TextureManager.h"

void Tile::Draw(SDL_Rect scr, SDL_Rect dest)
{

	SDL_RenderCopy(SDL_Game::m_pRenderer, m_pTexture, &scr, &dest);
}

Tile::Tile(SDL_Rect scr, SDL_Rect dest)
{
	mName = "Unkown";
	m_transform = dest;
}

void Tile::Renderer()
{
	//SDL_RenderCopy(SDL_Game::m_pRenderer, m_pTexture, nullptr, &m_transform);
}

void Tile::Update(double deltaTime)
{
	//
}

void Tile::OnCollision(Collider* pCollider)
{
	GameObject::OnCollision(pCollider);
}
