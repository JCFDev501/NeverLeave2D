#include "AiStatePatrol.h"
#include "Vector2.h"
#include "AiStateMachine.h"
#include "GameObject.h"

AiStatePatrol::AiStatePatrol(AiStateMachine* pOwner, GameObject* pTarget)
	:m_pOwner(pOwner)
	,m_pTarget(pTarget)
{

}

AiStatePatrol::~AiStatePatrol()
{
}

void AiStatePatrol::Enter()
{
	m_x = 0;
	m_y = -1;
}

void AiStatePatrol::Update(double deltaTime)
{
	using Vector2f = Vector2<float>;

	// Calculate a Linear path to the player.
	Vector2f directionToMove{ m_x, m_y };

	if (!Transitioned)
	{
		// Pass direction and delta time to Move().
		m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));

		Transitioned = true;
	}
	std::string q = m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));
	q = m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));
	if (q == "Solid" && (directionToMove.m_x == 0 && directionToMove.m_y == -1))
	{
		m_x = 1;
		m_y = 0;

		directionToMove = { m_x, m_y };

		m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));

	}

	q = m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));
	//q = m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));
	if (q == "Solid" && (directionToMove.m_x == 1 && directionToMove.m_y == 0))
	{
		m_x = 0;
		m_y = 1;

		directionToMove = { m_x, m_y };

		m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));

	}

	q = m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));

	if (q == "Solid" && (directionToMove.m_x == 0 && directionToMove.m_y == 1))
	{
		m_x = -1;
		m_y = 0;

		directionToMove = { m_x, m_y };

		m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));

	}

	q = m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));

	if (q == "Solid" && (directionToMove.m_x == -1 && directionToMove.m_y == 0))
	{
		m_x = 0;
		m_y = -1;

		directionToMove = { m_x, m_y };

		m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));
	}

	
}

