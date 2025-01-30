#pragma once
#include "RandomNumberGen.h"
#include "State.h"
#include "Vector2.h"
class AiStateMachine;
class GameObject;

class AiStateWonder : public State
{
	AiStateMachine* m_pOwner;

	GameObject* m_pTarget;

	float m_x = 0;
	float m_y = 0;
	bool mDecided = false;

	RandomNumberGen<int> mDirectionManager;

public:
	AiStateWonder(AiStateMachine* pOwner, GameObject* pTarget);
	~AiStateWonder();

	void Enter() override;

	void Update(double deltaTime) override;

	void GetNewDirection();
};

