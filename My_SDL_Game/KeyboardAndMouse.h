#pragma once
#include "DungeonCrawlerGame.h"
#include "PlayerCharacter.h"

class KeyboardAndMouse
{
public:
	KeyboardAndMouse();
	~KeyboardAndMouse() = default;

	int KeyboardAndMouseInputHandler(PlayerCharacter* pTarget, SDL_Event* pEvent, DungeonCrawlerGame* pOwner);

};

