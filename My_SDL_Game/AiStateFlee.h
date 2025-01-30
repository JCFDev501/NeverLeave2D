#pragma once
#include "State.h"
#include "Vector2.h"

class GameObject;
class AiStateMachine;

class AiStateFlee : public State
{
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

	float m_x = 0;
	float m_y = 0;

	bool Transitioned = false;

public:
	AiStateFlee(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateFlee();

	void Enter() override;

	void Update(double deltaTime) override;
};