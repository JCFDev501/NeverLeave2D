#include "Bat.h"

#include <iostream>

#include "CollisionManager.h"
#include "SDL_Game.h"

Bat::Bat(Vector2f position, Vector2f size, GameObject* pTarget, CollisionManager* pCollisionManager, float speed,
         float detectionRadius)
	:m_pTarget(pTarget)
	, m_kDetectDistanceSqr(detectionRadius * detectionRadius)
	, m_kSpeed(speed)
	, m_Position(position)
	, m_size(size)
	, m_Collider(this, SDL_Rect{ static_cast<int>(position.m_x), static_cast<int>(position.m_y), static_cast<int>(size.m_x), static_cast<int>(size.m_y) }, pCollisionManager)
	, m_pCollisionManager(pCollisionManager)
	,m_stateMachine(this, pTarget, AiStateMachine::StateName::Idle)
	,m_CurrentPhase(Phase1)
	,m_Fly("assets/Animations/bat.png", 8, 16, 16, 9, SDL_Game::m_pRenderer)
{
	mName = "Bat";
	mType = "Trigger";

	m_Fly.AddAnimation("fly", 0, 2);

	m_Fly.PlayAnimation("fly");
	

	m_x = m_Position.m_x;
	m_y = m_Position.m_y;

	m_pScream = Mix_LoadWAV("assets/MusicAndSound/BatScreech.wav");
	Mix_VolumeChunk(m_pScream, 100);
}

Bat::~Bat()
{
}

void Bat::Update(double deltaTime)
{
	m_Fly.Update(deltaTime);
	if (mHealth <= 0)
	{
		mHealth = 0;
		mActive = false;
		m_pCollisionManager->RemoveActiveCollider(&m_Collider);
	}

	if (mHealth <= 305)
	{
		m_CurrentPhase = Phase2;
	}

	if (mHealth <= 150)
	{
		m_CurrentPhase = Phase3;
	}


	if (m_CurrentPhase == Phase1)
	{
		m_stateMachine.ChangeToState(AiStateMachine::StateName::Idle);
	}
	else if (m_CurrentPhase == Phase2)
	{
		if (mScream)
		{
			Mix_PlayChannel(-1, m_pScream, 0);
			mScream = false;
		}

		Vector2f x = m_pTarget->GetPosition();

		// Calculate a Linear path to the player.
		Vector2f pathToTarget = x - this->GetPosition();

		// Check distance to player.
		if (pathToTarget.GetSquareLength() <= m_kDetectDistanceSqr)
		{
			m_stateMachine.ChangeToState(AiStateMachine::StateName::Chase);
		}
		else
		{
			m_stateMachine.ChangeToState(AiStateMachine::StateName::Idle);
		}

		m_stateMachine.Update(deltaTime);
	}
	else if (m_CurrentPhase == Phase3)
	{
		mScream = true;
		if (mScream)
		{
			Mix_PlayChannel(-1, m_pScream, 0);
			mScream = false;
		}

		m_stateMachine.ChangeToState(AiStateMachine::StateName::Wonder);
		m_stateMachine.Update(deltaTime);
	}
}

void Bat::Renderer()
{
	SDL_Rect transform{ static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_size.m_x), static_cast<int>(m_size.m_y) };
	m_Fly.SetTransform(transform);
	m_Fly.Render(SDL_Game::m_pRenderer);
	m_Collider.Render(SDL_Game::m_pRenderer);
}

void Bat::OnCollision(Collider* pCollider)
{
	if(m_CurrentPhase != Phase1)
	{
		if (pCollider->GetOwner()->GetName() == "FireBall")
		{
			mHealth -= 15;
			std::cout << "tims Health: " << mHealth << "\n";
			
		}
	}
	
}

std::string Bat::Move(Vector2<float> direction, float speedMultiplier)
{
	// Combine elements to get delta position.
	Vector2f deltaPosition = direction * speedMultiplier * m_kSpeed;

	// Perform the collision check.
	std::string didCollide = m_pCollisionManager->CheckForCollisionAndNotify(&m_Collider);

	// If movement occurred, update position.  
	if (didCollide.empty() || didCollide == "Trigger")
	{
		m_x += deltaPosition.m_x;
		m_y += deltaPosition.m_y;
		m_Collider.SetPosition(Vector2f{static_cast<float>(m_x), static_cast<float>(m_y)});
	}
	else if (didCollide == "Solidw")
	{
		m_x -= deltaPosition.m_x;
		m_y -= deltaPosition.m_y;
		m_Collider.SetPosition(Vector2f{ static_cast<float>(m_x), static_cast<float>(m_y) });
	}

	return didCollide;
}




