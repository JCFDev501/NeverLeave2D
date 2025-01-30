#pragma once
#include "State.h"
#include "Vector2.h"

class GameObject;
class AiStateMachine;

class AiStatePatrol : public State
{
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

	float m_x = 0;
	float m_y = 0;

	bool Transitioned = false;
	bool mHitTopLeft = false;
	bool mHitTopRight = false;
	bool mHitBottomLeft = false;
	bool mHitBottomRight = false;
	bool patrolStarted = false;

public:
	AiStatePatrol(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStatePatrol();

	void Enter() override;

	void Update(double deltaTime) override;
};