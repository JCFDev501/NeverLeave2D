#include "Floor.h"

#include <iostream>

#include "TextureManager.h"

Floor::Floor(SDL_Rect scr, SDL_Rect dest, const char* filename)
{
	mName = "Floor";

	m_transform = dest;

	auto position_x = static_cast<float>(m_transform.x);
	auto position_y = static_cast<float>(m_transform.y);

	m_pTexture = TextureManager::LoadTexture(filename);

}

void Floor::Renderer()
{
}

void Floor::Update(double deltaTime)
{
	Tile::Update(deltaTime);
}

void Floor::OnCollision(Collider* pCollider)
{
	Tile::OnCollision(pCollider);
}