#pragma once
#include "State.h"

class GameObject;
class AiStateMachine;

// An example AI state featuring chasing
class AiStateChase : public State
{
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

public:
	AiStateChase(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateChase();

	void Update(double deltaTime) override;
};

