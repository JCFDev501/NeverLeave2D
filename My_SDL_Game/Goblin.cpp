#include "Goblin.h"

Goblin::Goblin(Vector2f position, Vector2f size, GameObject* pTarget, CollisionManager* pCollisionManager, float speed,
	float detectionRadius)
	:GuardZombie(position, size, pTarget, pCollisionManager, speed, detectionRadius)
	,m_stateMachine(this, pTarget, AiStateMachine::StateName::Chase)
{
}

void Goblin::Update(double deltaTime)
{
	// TODO Add state transition condition

	m_stateMachine.Update(deltaTime);
}
