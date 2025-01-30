#include "SDL_Game.h"
#include <iostream>
#include <chrono>
#include "GameStateMachine.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>


SDL_Renderer* SDL_Game::m_pRenderer = nullptr;

SDL_Game::SDL_Game()
	:m_pWindow(nullptr)
	,m_pStateMachine(nullptr)
{
}

SDL_Game::~SDL_Game()
= default;

int SDL_Game::Initialize(GameStateMachine* pStateMachine)
{
	// Call to SDL_Init(). This will initialize SDL and the video subsystem.
	int errorCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
	if (errorCode == 0)
	{
		// print success message.
		std::cout << "SDL_Init() succeeded!!" << std::endl;
	}
	else
	{
		// Print error message and quit.
		std::cout << "SDL_Init() failed. Error code " << errorCode << ": " << SDL_GetError() << std::endl;
		system("pause");
		return errorCode;
	}

	// Attempts to create a maximized window that can be restored to a 640x480, centered window.
	m_pWindow = SDL_CreateWindow(
		"Basic Player Controls",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		960, 608,
		0);
	if (m_pWindow != nullptr)
	{
		// print success message.
		std::cout << "SDL_CreateWindow() succeeded!!" << std::endl;
	}
	else
	{
		// Print error message and quit.
		std::cout << "SDL_CreateWindow() failed. Error code " << errorCode << ": " << SDL_GetError() << std::endl;
		system("pause");
		return -1;
	}

	// Attempts to create a hardware-accelerated renderer for our window.
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_pRenderer != nullptr)
	{
		// print success message.
		std::cout << "SDL_CreateRenderer() succeeded!!" << std::endl;
	}
	else
	{
		// Print error message and quit.
		std::cout << "SDL_CreateRenderer() failed. Error code " << errorCode << ": " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return -1;
	}

	// Initialize SDL_ttf
	errorCode = TTF_Init();
	if (errorCode == 0)
	{
		std::cout << "TTF_Init() succeeded." << std::endl;
	}
	else
	{
		// error check failed
		std::cout << "TTF_Init() failed. Error code " << errorCode << ": " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return -1;
	}

	// Initialize SDL_Mixer.
	errorCode = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
		MIX_DEFAULT_CHANNELS, 1024);
	if (errorCode == 0)
	{
		std::cout << "Mix_OpenAudio() succeeded." << std::endl;
	}
	else
	{
		// error check failed
		std::cout << "Mix_OpenAudio() failed. Error code " << errorCode << ": " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return -1;
	}

	// Initialize MP3 support
	int audioFlags = MIX_INIT_MP3;
	errorCode = Mix_Init(audioFlags);
	if(errorCode != audioFlags)
	{
		// error check failed
		std::cout << "Mix_Init() failed. Error code " << Mix_GetError() << std::endl;
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		system("pause");
		return -1;
	}

	// Initialize state machine
	if (pStateMachine != nullptr && pStateMachine->Init())
	{
		std::cout << "State Machine succeeded!!" << std::endl;
		m_pStateMachine = pStateMachine;
	}
	else
	{
		std::cout << "Failed to create state machine." << std::endl;
		SDL_DestroyRenderer(m_pRenderer); // Destroy renderer
		SDL_DestroyWindow(m_pWindow); // Destroy window
		SDL_Quit(); // De-initialize SDL
		return -1;
	}

	// Success
	return 0;
}

void SDL_Game::RunGameLoop() 
{
	bool quit = false;

	// Gets the current time to store for the previous loop.
	auto lastFrameTime = std::chrono::high_resolution_clock::now();

	while(!quit)
	{
		// Get this frames time.
		auto thisFrameTime = std::chrono::high_resolution_clock::now();

		// Get the duration of time that has passed.
		std::chrono::duration<double> lastFrameDuration = thisFrameTime - lastFrameTime;

		// Convert duration into a double, which we use for delta time.
		const double deltaTime = lastFrameDuration.count();

		// Reset lastFrame to currentFrameTime.
		lastFrameTime = thisFrameTime;

		quit = ProcessInput(); // Check for input
		UpdateGameState(deltaTime); // update our game
		DisplayOutput(); // Display output

		if (mQuit)
			quit = true;
	}
} 

void SDL_Game::DeInitialize() const
{
	Mix_CloseAudio();
	SDL_DestroyRenderer(m_pRenderer); // Destroy renderer
	SDL_DestroyWindow(m_pWindow); // Destroy window
	SDL_Quit(); // De-initialize SDL
}

// Quit the game at the end of the current frame.
void SDL_Game::Quit()
{
	mQuit = true;
}

bool SDL_Game::ProcessInput() const
{
	if(m_pStateMachine == nullptr)
	{
		return true;
	}

	bool doQuit = false;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		doQuit = m_pStateMachine->HandleEvent(&event);
		if (doQuit == true)
			return true;      // do quit 
	}

	return false;            // do not quit
}

void SDL_Game::UpdateGameState(double deltaTime) const
{
	if (m_pStateMachine == nullptr)
	{
		return;
	}

	m_pStateMachine->UpdateCurrentState(deltaTime);
}

void SDL_Game::DisplayOutput() const
{
	if (m_pStateMachine == nullptr)
	{
		return;
	}

	m_pStateMachine->RenderCurrentState(m_pRenderer);
}
