#pragma once
#include "GuardZombie.h"
#include "AiStateMachine.h"

// An AI enemy that overrides Hard-codded behavior with a state machine. 
class Goblin : public GuardZombie
{
	using Vector2f = Vector2<float>;

	AiStateMachine m_stateMachine;

public:
	Goblin(Vector2f position, Vector2f size, GameObject* pTarget, CollisionManager* pCollisionManager,
		float speed = 80, float detectionRadius = 400);
	~Goblin();

	void Update(double deltaTime) override;

};

