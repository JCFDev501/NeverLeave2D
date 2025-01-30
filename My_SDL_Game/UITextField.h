#pragma once
#include <SDL_ttf.h>

#include "GameObject.h"
#include "Vector2.h"

class UITextField : public GameObject
{
	using Vector2 = Vector2<int>;
public:
	UITextField(TTF_Font* pFont, const char* pText, SDL_Color color, Vector2 postition, SDL_Renderer* pRenderer);
	~UITextField() override;

	// Gets called by the main loop each frame to render this object.
	void Renderer() override;
};

