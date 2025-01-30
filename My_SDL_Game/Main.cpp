#include <iostream>
#include <SDL.h>
#include "DungeonCrawlerGame.h"
#include "SDL_Game.h"


int main(int argc, char* argv[])
{
    // Allocates game manager.
    SDL_Game game;

    // Allocates game implementation.
    DungeonCrawlerGame DCG_StateMachine(&game);

    // Initialize game manager with state machine implementation
    game.Initialize(&DCG_StateMachine);

    // Run Game Loop
	game.RunGameLoop();

    // Clean Up
    game.DeInitialize();

    //Exit.
    return 0;
}