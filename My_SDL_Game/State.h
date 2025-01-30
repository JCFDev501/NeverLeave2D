#pragma once

// A general purpose state interface.
class State
{

public:
	State() {}
	virtual ~State() {}

	// Enters this state.
	virtual void Enter() {}

	// Updates this state
	virtual void Update(double deltaTime) {}

	// Exits this state
	virtual void Exit() {}

	
};