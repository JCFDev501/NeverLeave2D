#pragma once

class State;
class GameObject;

// A basic state Machine for AI.
class AiStateMachine
{
public:
	enum StateName
	{
		None,
		Idle,
		Chase,
		Flee,
		Wonder
	};

private:

	GameObject* m_pOwner;

	GameObject* m_pTarget;

	State* m_pCurrentState;

	// Currently active state name.
	// we'll use this to check if we are all ready in a state.
	StateName m_currentStateName;

public:
	AiStateMachine(GameObject* pOwner, GameObject* pTarget, StateName initialState);
	~AiStateMachine();

	void Update(double deltaTime);

	void ChangeToState(StateName state);

	[[nodiscard]] GameObject* GetOwner() const { return m_pOwner; }


};

