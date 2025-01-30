#pragma once
#include <SDL_ttf.h>

#include "BackGround.h"
#include "GameObject.h"

class PlayerCharacter;

class Ui : public GameObject 
{
	PlayerCharacter* m_pPlayer;
	BackGround mUiBackground;
	TTF_Font* m_pFont;

public:
	Ui(SDL_Rect transform, SDL_Renderer* pRenderer, PlayerCharacter* pPlayer, TTF_Font* pFont);
	~Ui() override;
	void Update(double deltaTime) override;
	void Renderer() override;
};

