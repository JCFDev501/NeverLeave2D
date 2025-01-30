#include "Key.h"

#include "CollisionManager.h"
#include "SDL_Game.h"

Key::Key(SDL_Rect transform, CollisionManager* pCollisionManager)
	:mSpin("assets/Animations/KeyBlue.png", 10, 32, 32, 8, SDL_Game::m_pRenderer)
	, m_collider(this, transform, pCollisionManager)
	, m_pCollisionManager(pCollisionManager)
{
	mName = "Key";
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

	m_collider.SetTransForm(Vector2<float>{position_x, position_y}, Vector2<float>{size_w, size_h});

	mSpin.SetTransform(m_transform);
	mSpin.AddAnimation("spin", 0, 11);
	mSpin.PlayAnimation("spin");
}

Key::~Key()
{
	SDL_DestroyTexture(m_pTexture);
}

void Key::Update(double deltaTime)
{
	mSpin.Update(deltaTime);
}

void Key::Renderer()
{
	mSpin.Render(SDL_Game::m_pRenderer);
	m_collider.Render(SDL_Game::m_pRenderer);
}

void Key::OnCollision(Collider* pCollider)
{
	if (pCollider->GetOwner()->GetName() == "Player")
	{
		mActive = false;
		m_pCollisionManager->RemoveActiveCollider(&m_collider);
	}

}