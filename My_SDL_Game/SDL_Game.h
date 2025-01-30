#pragma once

#include <SDL.h>
#include "TileMap.h"

class GameStateMachine;

class SDL_Game
{
	// Pointer to the application window managed by SDL.
	SDL_Window* m_pWindow;

	// Pointer to the state machine for managing game states
	GameStateMachine* m_pStateMachine;

	// whether to quit at the end of the current frame.
	bool mQuit = false;

public:
	SDL_Game(); // Constructor
	~SDL_Game(); // DeConstructor

	// Attempts to initialize SDL. Returns error code (0 means success)
	int Initialize(GameStateMachine* pStateMachine);

	// Runs the game loop. Won't exit until a quit event has been detected.
	void RunGameLoop();

	// De-initializes SDL.
	void DeInitialize() const;

	static SDL_Renderer* m_pRenderer;

	double mCurrentFrameRate = 12;

	// Quit the game at the end of the current frame.
	void Quit();

private:

	// Processes events received by SDL. Returns weather ot not an exit event has been detected.
	[[nodiscard]] bool ProcessInput() const;

	//Updates the state of the game simulation based on the passage of time and any events that were detected.
	void UpdateGameState(double deltaTime) const;

	// Draws this programs output
	void DisplayOutput() const;

	
	

};

