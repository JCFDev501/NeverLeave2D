#include "Switch.h"

#include "TextureManager.h"

Switch::Switch(SDL_Rect transform, CollisionManager* pCollisionManager)
	:mcollider(this, m_transform, pCollisionManager)
	,m_activeSoundChannel(-1)
{
	mName = "Door";
	mType = "Trigger";
	mPositionX = transform.x;
	mPositionY = transform.y;
	m_transform.x = transform.x;
	m_transform.y = transform.y;
	m_transform.w = transform.w;
	m_transform.h = transform.h;
	mSpeed = 0;

	auto position_x = static_cast<float>(transform.x + 20);
	auto position_y = static_cast<float>(transform.y + 20);
	

	mcollider.SetTransForm(Vector2{position_x, position_y}, Vector2<float>{8, 8});
	m_pTexture = TextureManager::LoadTexture("assets/Swich1.png");
	m_pSound = Mix_LoadWAV("assets/MusicAndSound/Lever_Switch.wav");
}

Switch::~Switch()
{
	SDL_DestroyTexture(m_pTexture);

	if (m_pSound != nullptr)
	{
		Mix_FreeChunk(m_pSound);
		m_pSound = nullptr;
	}
}

void Switch::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Switch::Renderer()
{
	TextureManager::Draw(m_pTexture, m_transform);
	mcollider.Render(SDL_Game::m_pRenderer);
	
}

void Switch::OnCollision(Collider* pCollider)
{
	mFlipped = true;

	Mix_PlayChannel(-1, m_pSound, 0);

	m_pTexture = TextureManager::LoadTexture("assets/Swich2.png");
}
