#include "Ghost.h"

#include <iostream>

#include "CollisionManager.h"
#include "TextureManager.h"


Ghost::Ghost(float x, float y, CollisionManager* pCollisionManager)
	:mStamina(10)
	, m_Movement("assets/Animations/Enemy_Movement_Sprite_Sheet.png", 12, 64, 64, 32, SDL_Game::m_pRenderer)
	, m_collider(this, mBoxColider, pCollisionManager)
	, m_pCollisionManager(pCollisionManager)
{
	mName = "EvilTim";
	m_x = x;
	m_y = y;
	m_transform.x = static_cast<int>(x);
	m_transform.y = static_cast<int>(y);
	m_transform.w = s_width;
	m_transform.h = s_length;
	mSpeed = 120.00;
	mCurrentDirection = mDown;

	m_Movement.AddAnimation("idleFront", 0, 0);
	m_Movement.AddAnimation("idleBack", 4, 4);
	m_Movement.AddAnimation("walkFront", 0, 3);
	m_Movement.AddAnimation("walkBack", 4, 7);
}

Ghost::~Ghost()
{
	SDL_DestroyTexture(m_pTexture);
}


void Ghost::Renderer()
{
	m_Movement.Render(SDL_Game::m_pRenderer);
	m_collider.Render(SDL_Game::m_pRenderer);
	
}

void Ghost::OnCollision(Collider* pCollider)
{
	if (m_Movement.GetAnimationState() == "walkFront")
	{
		if (pCollider->GetOwner()->GetName() == "Wall")
		{
			mCurrentDirection = mUp;
		}
	}
	else if (m_Movement.GetAnimationState() == "walkBack")
	{
		if (pCollider->GetOwner()->GetName() == "Wall")
		{
			mCurrentDirection = mDown;
		}
	}
	
	if (pCollider->GetOwner()->GetName() == "FireBall")
	{
		mHealth -= 10;
		std::cout << "tims Health: " << mHealth << "\n";
	}
	
}

void Ghost::MovementManager(double deltaTime)
{
	// update the transform.
	m_transform.x = static_cast<int>(m_x);
	m_transform.y = static_cast<int>(m_y);

	m_Movement.SetTransform(m_transform);

	float position_x = static_cast<float>(m_Movement.GetTransform().x + 17);
	float position_y = static_cast<float>(m_Movement.GetTransform().y + 17);
	float size_w = static_cast<float>(mBoxColider.w);
	float size_h = static_cast<float>(mBoxColider.h);

	m_collider.SetTransForm(Vector2{ position_x, position_y }, Vector2{ size_w, size_h });

	// Change in position.
	const double deltaPosition = mSpeed * deltaTime;


	if (mCurrentDirection.x == mDown.x && mCurrentDirection.y == mDown.y)
	{
		const std::string collided = m_collider.TryMove(Vector2<float>{ 0, 1 });
		if (collided.empty() || collided == "DamageZone" || collided == "HealZone" || collided == "WinZone")
		{
				m_y += deltaPosition;
				m_Movement.SetAnimationState("walkFront");
		}
	}
	if (mCurrentDirection.x == mUp.x && mCurrentDirection.y == mUp.y)
	{
		const std::string collided = m_collider.TryMove(Vector2<float>{ 0, -1 });
		if (collided.empty() || collided == "DamageZone" || collided == "HealZone" || collided == "WinZone")
		{
				m_y -= deltaPosition;
				m_Movement.SetAnimationState("walkBack");
		}
	}
}

void Ghost::AnimationManager()
{
	m_Movement.GetAnimationState();

	if (m_Movement.GetAnimationState() == "walkFront")
	{
		m_Movement.PlayAnimation("walkFront");
	}
	else if (m_Movement.GetAnimationState() == "walkBack")
	{
		m_Movement.PlayAnimation("walkBack");
	}
}

void Ghost::Update(double deltaTime)
{
	m_Movement.Update(deltaTime);
	AnimationManager();
	MovementManager(deltaTime);

	if (mHealth <= 0)
	{
		mActive = false;
		m_pCollisionManager->RemoveActiveCollider(&m_collider);
	}
}
