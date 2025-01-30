#include "FireBall.h"

#include <iostream>

#include "CollisionManager.h"
#include "SDL_Game.h"


FireBall::FireBall(CollisionManager* pCollisionManager, double x, double y)
	:mSpin("assets/FireBall.png", 12, 16, 16, 5, SDL_Game::m_pRenderer)
	,m_collider(this, mBoxColider, pCollisionManager)
	,m_pCollisionManager(pCollisionManager)
{
	mName = "FireBall";
	mType = "Trigger";

	mSpin.AddAnimation("hurl", 0, 4);
	mSpin.PlayAnimation("hurl");

	m_x = x;
	m_y = y;
	m_transform.x = static_cast<int>(x);
	m_transform.y = static_cast<int>(y);
}

FireBall::~FireBall()
{
}

void FireBall::Update(double deltaTime)
{
	MovementManager(deltaTime);
	mSpin.Update(deltaTime);
}

void FireBall::Renderer()
{
	mSpin.Render(SDL_Game::m_pRenderer);
	m_collider.Render(SDL_Game::m_pRenderer);
}

void FireBall::OnCollision(Collider* pCollider)
{
	if(pCollider->GetOwner()->GetType() == "Solidw")
	{
		m_pCollisionManager->RemoveActiveCollider(&m_collider);
		mFireBallHitTest = true;
	}

	if (pCollider->GetOwner()->GetName() == "Wall" || pCollider->GetOwner()->GetName() == "Chest")
	{
		m_pCollisionManager->RemoveActiveCollider(&m_collider);
		mFireBallHitTest = true;
	}
	if (pCollider->GetOwner()->GetName() == "EvilTim" || pCollider->GetOwner()->GetName() == "Bat" || pCollider->GetOwner()->GetName() == "ZombieGuard")
	{
		m_pCollisionManager->RemoveActiveCollider(&m_collider);
		mFireBallHitTest = true;
	}
}

void FireBall::MovementManager(double deltaTime)
{
	mSpin.SetTransform(m_transform);

	float position_x = static_cast<float>(mSpin.GetTransform().x);
	float position_y = static_cast<float>(mSpin.GetTransform().y);
	float size_w = static_cast<float>(mBoxColider.w);
	float size_h = static_cast<float>(mBoxColider.h);

	m_collider.SetTransForm(Vector2{ position_x, position_y }, Vector2{ size_w, size_h });
	// update the transform.
	m_transform.x = static_cast<int>(m_x);
	m_transform.y = static_cast<int>(m_y);

	// Change in position.
	mSpeed = 300;
	const double deltaPosition = mSpeed * deltaTime;

	if (mCurrentDirection.x == mRight.x && mCurrentDirection.y == mRight.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 1, 0 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x += deltaPosition;
		}
	}
	else if (mCurrentDirection.x == mLeft.x && mCurrentDirection.y == mLeft.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ -1, 0 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x -= deltaPosition;
		}
	}
	else if (mCurrentDirection.x == mUp.x && mCurrentDirection.y == mUp.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 0, 1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_y -= deltaPosition;
		}
	}
	else if (mCurrentDirection.x == mDown.x && mCurrentDirection.y == mDown.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 0, -1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_y += deltaPosition;
		}
	}

	if (mCurrentDirection.x == mUpRight.x && mCurrentDirection.y == mUpRight.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 1, -1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x += deltaPosition;
			m_y -= deltaPosition;
		}
	}
	else if (mCurrentDirection.x == mUpLeft.x && mCurrentDirection.y == mUpLeft.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ -1, -1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x -= deltaPosition;
			m_y -= deltaPosition;
		}
	}
	else if (mCurrentDirection.x == mDownRight.x && mCurrentDirection.y == mDownRight.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 1, 1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x += deltaPosition;
			m_y += deltaPosition;
		}
	}
	else if (mCurrentDirection.x == mDownLeft.x && mCurrentDirection.y == mDownLeft.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ -1, 1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x -= deltaPosition;
			m_y += deltaPosition;
		}
	}
	


}
