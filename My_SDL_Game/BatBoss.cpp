#include "BatBoss.h"

#include <iostream>

#include "CollisionManager.h"
#include "TextureManager.h"


BatBoss::BatBoss(double x, double y, CollisionManager* pCollisionManager)
	:mStamina(10)
	, m_Movement("assets/Animations/bat.png", 6, 16, 16, 9, SDL_Game::m_pRenderer)
	, m_collider(this, mBoxColider, pCollisionManager)
	, m_pCollisionManager(pCollisionManager)
{
	mName = "BatBoss";
	m_x = x;
	m_y = y;
	m_transform.x = static_cast<int>(x);
	m_transform.y = static_cast<int>(y);
	m_transform.w = s_width;
	m_transform.h = s_length;
	mSpeed = 120.00;
	mCurrentDirection = mDown;

	m_Movement.AddAnimation("moveRight", 0, 2);
	m_Movement.AddAnimation("moveLeft", 3, 5);
	m_Movement.AddAnimation("moveDown", 6, 8);

	m_Movement.PlayAnimation("moveRight");
	
}

BatBoss::~BatBoss()
{
	SDL_DestroyTexture(m_pTexture);
}


void BatBoss::Renderer()
{
	m_Movement.Render(SDL_Game::m_pRenderer);
	m_collider.Render(SDL_Game::m_pRenderer);
}

void BatBoss::OnCollision(Collider* pCollider)
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
		std::cout << "boss Health: " << mHealth << "\n";
	}

}

void BatBoss::MovementManager(double deltaTime)
{
	// update the transform.
	m_transform.x = static_cast<int>(m_x);
	m_transform.y = static_cast<int>(m_y);

	m_Movement.SetTransform(m_transform);

	float position_x = static_cast<float>(m_Movement.GetTransform().x + 45);
	float position_y = static_cast<float>(m_Movement.GetTransform().y + 50);
	float size_w = static_cast<float>(mBoxColider.w);
	float size_h = static_cast<float>(mBoxColider.h);

	m_collider.SetTransForm(Vector2{ position_x, position_y }, Vector2{ size_w, size_h });

	//// Change in position.
	//const double deltaPosition = mSpeed * deltaTime;
	//
	//
	//if (mCurrentDirection.x == mDown.x && mCurrentDirection.y == mDown.y)
	//{
	//	const std::string collided = m_collider.TryMove(Vector2{ 0, 1 });
	//	if (collided.empty() || collided == "DamageZone" || collided == "HealZone" || collided == "WinZone")
	//	{
	//		m_y += deltaPosition;
	//		m_Movement.SetAnimationState("walkFront");
	//	}
	//}
	//if (mCurrentDirection.x == mUp.x && mCurrentDirection.y == mUp.y)
	//{
	//	const std::string collided = m_collider.TryMove(Vector2{ 0, -1 });
	//	if (collided.empty() || collided == "DamageZone" || collided == "HealZone" || collided == "WinZone")
	//	{
	//		m_y -= deltaPosition;
	//		m_Movement.SetAnimationState("walkBack");
	//	}
	//}
}

void BatBoss::AnimationManager()
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

void BatBoss::Update(double deltaTime)
{
	m_Movement.Update(deltaTime);
	//AnimationManager();
	MovementManager(deltaTime);

	if (mHealth <= 0)
	{
		mActive = false;
		m_pCollisionManager->RemoveActiveCollider(&m_collider);
	}
}