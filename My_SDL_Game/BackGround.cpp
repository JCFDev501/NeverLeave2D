#include "BackGround.h"

#include <iostream>
#include <SDL_image.h>

#include "TextureManager.h"

BackGround::BackGround(SDL_Rect transform, const char* fileName, SDL_Renderer* pRenderer)
	:m_pTexture2(nullptr)
{
	mName = "BackGround";
	m_transform = transform;

	// load image
	SDL_Surface* pImageSurface = IMG_Load(fileName);
	if (pImageSurface == nullptr)
	{
		std::cout << "image loading failed. Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Convert surface to texture
	m_pTexture2 = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);

	if (m_pTexture2 == nullptr)
	{
		std::cout << "Texture loading failed. Error: " << SDL_GetError() << std::endl;
	}
	// Free surface
	SDL_FreeSurface(pImageSurface);
}

BackGround::~BackGround()
{
	SDL_DestroyTexture(m_pTexture2);
}

void BackGround::Renderer()
{
	SDL_RenderCopy(SDL_Game::m_pRenderer, m_pTexture2, nullptr, &m_transform);
}
