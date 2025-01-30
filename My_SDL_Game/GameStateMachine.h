#pragma once
#include <SDL.h>

// An interface for handling game states / scenes

class GameState;

class GameStateMachine
{
public:
	virtual ~GameStateMachine() = default;

	// Update the current game state.
	virtual void UpdateCurrentState(double deltaTime) = 0;

	// Render the current game state.
	virtual void RenderCurrentState(SDL_Renderer* pRenderer) = 0;

	// Handle the given event within the current state.
	virtual bool HandleEvent(SDL_Event* pEvent) = 0;

	//Exits current state and enters new state
	virtual void ChangeState(GameState* pNewState) = 0;

	virtual bool Init() = 0;
};

