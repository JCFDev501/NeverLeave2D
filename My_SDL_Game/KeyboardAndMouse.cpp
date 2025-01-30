#include "KeyboardAndMouse.h"

#include <iostream>

KeyboardAndMouse::KeyboardAndMouse()

{
}

int KeyboardAndMouse::KeyboardAndMouseInputHandler(PlayerCharacter* pTarget, SDL_Event* pEvent, DungeonCrawlerGame* pOwner)
{
	// Process any events until there are none left.

	const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
	// There are events to process.

	// Check the events type to know what it is.
	switch (pEvent->type)
	{

	case SDL_MOUSEBUTTONUP:
	{
		pTarget->mCastedFireBall = true;
	}
	break;

	case SDL_KEYUP:
	{
		if (pEvent->key.keysym.sym == SDLK_k)
		{
			return 3;
		}
		// Player Movement
		// if player releases d and presses another key
		if (pEvent->key.keysym.sym == SDLK_d)
		{
			if (keyboard_state[SDL_SCANCODE_W])
			{
				pTarget->SetDirection(0, 1);

			}
			else if (keyboard_state[SDL_SCANCODE_A])
			{
				pTarget->SetDirection(-1, 0);
			}
			else if (keyboard_state[SDL_SCANCODE_S])
			{
				pTarget->SetDirection(0, -1);
			}
			else
			{
				pTarget->SetDirection(0, 0);
			}
		}
		// if player releases a and presses another key
		if (pEvent->key.keysym.sym == SDLK_a)
		{
			if (keyboard_state[SDL_SCANCODE_W])
			{
				pTarget->SetDirection(0, 1);
			}
			else if (keyboard_state[SDL_SCANCODE_D])
			{
				pTarget->SetDirection(1, 0);
			}
			else if (keyboard_state[SDL_SCANCODE_S])
			{
				pTarget->SetDirection(0, -1);
			}
			else
			{
				pTarget->SetDirection(0, 0);
			}
		}
		// if player releases w and presses another key
		if (pEvent->key.keysym.sym == SDLK_w)
		{
			if (keyboard_state[SDL_SCANCODE_S])
			{
				pTarget->SetDirection(0, -1);
			}
			else if (keyboard_state[SDL_SCANCODE_A])
			{
				pTarget->SetDirection(-1, 0);
			}
			else if (keyboard_state[SDL_SCANCODE_D])
			{
				pTarget->SetDirection(1, 0);
			}
			else
			{
				pTarget->SetDirection(0, 0);
			}
		}
		// if player releases s and presses another key
		if (pEvent->key.keysym.sym == SDLK_s)
		{
			if (keyboard_state[SDL_SCANCODE_W])
			{
				pTarget->SetDirection(0, 1);
			}
			else if (keyboard_state[SDL_SCANCODE_A])
			{
				pTarget->SetDirection(-1, 0);
			}
			else if (keyboard_state[SDL_SCANCODE_D])
			{
				pTarget->SetDirection(1, 0);
			}
			else
			{
				pTarget->SetDirection(0, 0);
			}

		}
		// if you release the shift key	 
		if (pEvent->key.keysym.sym == SDLK_LSHIFT)
		{
			pTarget->SetSpeed(100.0);
		}
	}
	// IF THE EVENT WAS A WINDOW EVENT...
	break;

	case SDL_WINDOWEVENT:
	{
		// IF THE WINDOW EVENT WAS CLOSE WINDOW	
		if (pEvent->window.event == SDL_WINDOWEVENT_CLOSE)
		{
			return true;
		}
	}
	break;

	case SDL_KEYDOWN:
	{
		// QUIT
		if (keyboard_state[SDL_SCANCODE_LCTRL] && keyboard_state[SDL_SCANCODE_Q])
		{
			return true;
		}

		// Player START Movements

		if (keyboard_state[SDL_SCANCODE_D] && keyboard_state[SDL_SCANCODE_W])
		{
			pTarget->SetDirection(1, 1);

		}
		else if (keyboard_state[SDL_SCANCODE_A] && keyboard_state[SDL_SCANCODE_W])
		{
			pTarget->SetDirection(1, -1);
		}
		else if (keyboard_state[SDL_SCANCODE_S] && keyboard_state[SDL_SCANCODE_D])
		{
			pTarget->SetDirection(-1, -1);
		}
		else if (keyboard_state[SDL_SCANCODE_S] && keyboard_state[SDL_SCANCODE_A])
		{
			pTarget->SetDirection(-1, 1);
		}
		else if (keyboard_state[SDL_SCANCODE_D])
		{
			pTarget->SetDirection(1, 0);
		}
		else if (keyboard_state[SDL_SCANCODE_A])
		{
			pTarget->SetDirection(-1, 0);
		}
		else if (keyboard_state[SDL_SCANCODE_W])
		{
			pTarget->SetDirection(0, 1);
		}
		else if (keyboard_state[SDL_SCANCODE_S])
		{
			pTarget->SetDirection(0, -1);
		}
		else
		{
			std::cout << "[Key is Not Available]\n";
		}

		// Player sprinting (If you press left shift and any movement key)
		if (keyboard_state[SDL_SCANCODE_LSHIFT] && keyboard_state[SDL_SCANCODE_D])
		{
			pTarget->SetSpeed(300.0);
		}
		else if (keyboard_state[SDL_SCANCODE_LSHIFT] && keyboard_state[SDL_SCANCODE_A])
		{
			pTarget->SetSpeed(300.0);
		}
		else if (keyboard_state[SDL_SCANCODE_LSHIFT] && keyboard_state[SDL_SCANCODE_S])
		{
			pTarget->SetSpeed(300.0);
		}
		else if (keyboard_state[SDL_SCANCODE_LSHIFT] && keyboard_state[SDL_SCANCODE_W])
		{
			pTarget->SetSpeed(300.0);
		}

	}
	break;

	}
	return false;
}
