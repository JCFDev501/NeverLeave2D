#include "AiStateChase.h"
#include "Vector2.h"
#include "AiStateMachine.h"
#include "GameObject.h"

AiStateChase::AiStateChase(AiStateMachine* pOwner, GameObject* pTarget)
	:m_pOwner(pOwner)
	,m_pTarget(pTarget)
{
}

AiStateChase::~AiStateChase()
{
}

void AiStateChase::Update(double deltaTime)
{
	using Vector2f = Vector2<float>;
	
	// Calculate a Linear path to the player.
	Vector2f pathToTarget = m_pTarget->GetPosition() - m_pOwner->GetOwner()->GetPosition();
	
	// If Player is close, normalize the path to get direction.
	Vector2f directionToTarget = pathToTarget.GetNormalized();

	// Pass direction and delta time to Move().
	m_pOwner->GetOwner()->Move(directionToTarget, static_cast<float>(deltaTime));
}
