#pragma once
#include "GameObject.h"

// Renders Menu BackGround
class BackGround : public GameObject
{
	SDL_Texture* m_pTexture2;

public:
	BackGround(SDL_Rect transform, const char* fileName ,SDL_Renderer* pRenderer);
	~BackGround() override;

	void Renderer() override;
};

