#include "AiStateWonder.h"

#include "AiStateMachine.h"
#include "Collider.h"
#include "GameObject.h"
#include "Vector2.h"

AiStateWonder::AiStateWonder(AiStateMachine* pOwner, GameObject* pTarget)
	:m_pOwner(pOwner)
	,m_pTarget(pTarget)
	,mDirectionManager(0, 2)
{
}

AiStateWonder::~AiStateWonder()
{
}

void AiStateWonder::Enter()
{
	const int randNumberX = mDirectionManager.GetRandomNumberInt() - 1;
	const int randNumberY = mDirectionManager.GetRandomNumberInt() - 1;

	m_x = static_cast<float>(randNumberX);
	m_y = static_cast<float>(randNumberY);

	if (m_x == 0.f && m_y == 0.f)
		Enter();
}

void AiStateWonder::Update(double deltaTime)
{
	using Vector2f = Vector2<float>;

	const Vector2f directionToMove = {m_x, m_y};

	std::string collided = m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));

	if (collided == "Solidw")
	{
		GetNewDirection();
		collided = m_pOwner->GetOwner()->Move(directionToMove, static_cast<float>(deltaTime));
	}
		

}

void AiStateWonder::GetNewDirection()
{
	const int randNumberX = mDirectionManager.GetRandomNumberInt() - 1;
	const int randNumberY = mDirectionManager.GetRandomNumberInt() - 1;

	m_x = static_cast<float>(randNumberX);
	m_y = static_cast<float>(randNumberY);

	if (m_x == 0.f && m_y == 0.f)
		GetNewDirection();
}
