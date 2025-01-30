#include "Boxes.h"

#include "TextureManager.h"

Boxes::Boxes(SDL_Rect transform, CollisionManager* pCollisionManager)
	:m_collider(this, m_transform, pCollisionManager)
{
	mName = "box";
	mPositionX = transform.x;
	mPositionY = transform.y;
	m_transform.x = transform.x;
	m_transform.y = transform.y;
	m_transform.w = transform.w;
	m_transform.h = transform.h;
	mSpeed = 0;
	//m_collider.SetTransForm(m_transform);   
	//m_pTexture = TextureManager::LoadTexture("assets/dungeon_box.png");
}

Boxes::~Boxes()
{
	SDL_DestroyTexture(m_pTexture);
}

void Boxes::Renderer()
{
	SDL_RenderCopy(SDL_Game::m_pRenderer, m_pTexture, nullptr, &m_transform);
	m_collider.Render(SDL_Game::m_pRenderer);
}

void Boxes::Update(double deltaTime)
{
}
