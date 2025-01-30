#include "GuardZombie.h"

#include <iostream>

#include "CollisionManager.h"
#include "SDL_Game.h"

GuardZombie::GuardZombie(Vector2f position, Vector2f size, GameObject* pTarget, CollisionManager* pCollisionManager,
                         float speed, float detectionRadius)
	:m_pTarget(pTarget)
	,m_kDetectDistanceSqr(detectionRadius * detectionRadius)
	,m_kSpeed(speed)
	,m_Position(position)
	,m_size(size)
	,m_Collider(this,SDL_Rect{ static_cast<int>(position.m_x), static_cast<int>(position.m_y), static_cast<int>(size.m_x), static_cast<int>(size.m_y)}, pCollisionManager)
	,m_pCollisionManager(pCollisionManager)
	,m_Fly("assets/Animations/bat.png", 8, 16, 16, 9, SDL_Game::m_pRenderer)
{
	mName = "ZombieGuard";
	mType = "Trigger";

	m_Fly.AddAnimation("fly", 0, 2);

	m_Fly.PlayAnimation("fly");
}

GuardZombie::~GuardZombie()
{
	m_pCollisionManager->RemoveActiveCollider(&m_Collider);
}

void GuardZombie::Update(double deltaTime)
{
	m_Fly.Update(deltaTime);

	if (mHealth <= 0 && mActive == true)
	{
		mHealth = 0;
		mActive = false;
		m_pCollisionManager->RemoveActiveCollider(&m_Collider);
	}

	// Calculate a Linear path to the player.
	Vector2f x{ this->GetPosition().m_x - 32, this->GetPosition().m_y - 32 };
	Vector2f pathToTarget = m_pTarget->GetPosition() - x;

	// Check distance to player.
	if(pathToTarget.GetSquareLength() <= m_kDetectDistanceSqr)
	{
		// If Player is close, normalize the path to get direction.
		Vector2f directionToTarget = pathToTarget.GetNormalized();

		// Pass direction and delta time to Move().
		Move(directionToTarget, static_cast<float>(deltaTime));
	}
	
}

void GuardZombie::Renderer()
{
	SDL_Rect transform { static_cast<int>(m_Position.m_x), static_cast<int>(m_Position.m_y), static_cast<int>(m_size.m_x), static_cast<int>(m_size.m_y)};

	m_Fly.SetTransform(transform);
	m_Fly.Render(SDL_Game::m_pRenderer);
	m_Collider.Render(SDL_Game::m_pRenderer);
}

void GuardZombie::OnCollision(Collider* pCollider)
{
	if (pCollider->GetOwner()->GetName() == "FireBall")
	{
		mHealth -= 25;
	}
}

std::string GuardZombie::Move(Vector2<float> direction, float speedMultiplier)
{

	// Combine elements to get delta position.
	Vector2f deltaPosition = direction * speedMultiplier * m_kSpeed;

	// Perform the collision check.
	std::string didCollide = m_pCollisionManager->CheckForCollisionAndNotify(&m_Collider);

	// If movement occurred, update position.  
	if (didCollide.empty() || didCollide == "Trigger" || didCollide == "Solidw" || didCollide == "Solid")
	{
		m_Position.m_x += deltaPosition.m_x;
		m_Position.m_y += deltaPosition.m_y;
		m_Collider.SetPosition(m_Position);
	}
	return didCollide;
}
