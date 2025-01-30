#include "UITextField.h"

#include "SDL_Game.h"

UITextField::UITextField(TTF_Font* pFont, const char* pText, SDL_Color color, Vector2 postition,
                         SDL_Renderer* pRenderer)
{
	m_pTexture = nullptr;

	// Create the surface from the text and the font.
	SDL_Surface* pTextSurface = TTF_RenderText_Solid(pFont, pText, color);

	// Create the texture.
	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);

	// Get the dimensions of the text and apply them to m_transform.
	m_transform.x = postition.m_x;
	m_transform.y = postition.m_y;

	m_transform.w = pTextSurface->w;
	m_transform.h = pTextSurface->h;


	SDL_FreeSurface(pTextSurface);
}

UITextField::~UITextField()
{
	SDL_DestroyTexture(m_pTexture);
}

void UITextField::Renderer()
{
	SDL_RenderCopy(SDL_Game::m_pRenderer, m_pTexture, nullptr, &m_transform);
}
