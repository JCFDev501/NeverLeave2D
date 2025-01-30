#include "DumbGhost.h"

#include <iostream>

#include "RandomNumberGen.h"
#include "SDL_Game.h"

DumbGhost::DumbGhost(Vector2f position, Vector2f size, GameObject* pTarget, CollisionManager* pCollisionManager,
                     float speed, float detectionRadius)
	:m_pTarget(pTarget)
	, m_kDetectDistanceSqr(detectionRadius* detectionRadius)
	, m_kSpeed(speed)
	, m_Position(position)
	, m_size(size)
	, m_Collider(this, SDL_Rect{ static_cast<int>(position.m_x), static_cast<int>(position.m_y), static_cast<int>(size.m_x - 16), static_cast<int>(size.m_y - 16) }, pCollisionManager)
	, m_pCollisionManager(pCollisionManager)
	, m_stateMachine(this, pTarget, AiStateMachine::StateName::Idle)
	, m_Float("assets/Animations/DumbGhost.png", 9, 64, 64, 5, SDL_Game::m_pRenderer)
{
	mName = "DumbGhost";
	mType = "Trigger";

	m_Float.AddAnimation("float", 0, 4);

	m_Float.PlayAnimation("float");

	m_x = m_Position.m_x;
	m_y = m_Position.m_y;

	RandomNumberGen<int> randomNum(0, 1);

	int randnum = randomNum.GetRandomNumberInt();

	if (randnum == 0)
	{
		m_stateMachine.ChangeToState(AiStateMachine::StateName::Wonder);
	}
	else
	{
		m_stateMachine.ChangeToState(AiStateMachine::StateName::Chase);
	}
	
}

DumbGhost::~DumbGhost()
{
}

void DumbGhost::Update(double deltaTime)
{
	m_Float.Update(deltaTime);
	if (mHealth <= 0)
	{
		mHealth = 0;
		mActive = false;
		m_pCollisionManager->RemoveActiveCollider(&m_Collider);
	}
	m_stateMachine.Update(deltaTime);
}

void DumbGhost::Renderer()
{
	SDL_Rect transform{ static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_size.m_x), static_cast<int>(m_size.m_y) };
	m_Float.SetTransform(transform);
	m_Float.Render(SDL_Game::m_pRenderer);
	m_Collider.Render(SDL_Game::m_pRenderer);
}

void DumbGhost::OnCollision(Collider* pCollider)
{

	if (pCollider->GetOwner()->GetName() == "FireBall")
	{
		mHealth -= 50;
	}
}

std::string DumbGhost::Move(Vector2<float> direction, float speedMultiplier)
{
	// Combine elements to get delta position.
	Vector2f deltaPosition = direction * speedMultiplier * m_kSpeed;

	// Perform the collision check.
	std::string didCollide = m_pCollisionManager->CheckForCollisionAndNotify(&m_Collider);

	// If movement occurred, update position.  
	if (didCollide.empty() || didCollide == "Trigger" || didCollide == "Solid")
	{
		m_x += deltaPosition.m_x;
		m_y += deltaPosition.m_y;
		m_Collider.SetPosition(Vector2f{ static_cast<float>(m_x + 10), static_cast<float>(m_y + 10) });
	}
	else if (didCollide == "Solidw")
	{
		m_x -= deltaPosition.m_x * 2;
		m_y -= deltaPosition.m_y * 2;
		m_Collider.SetPosition(Vector2f{ static_cast<float>(m_x + 10), static_cast<float>(m_y + 10) });
	}

	return didCollide;
}
