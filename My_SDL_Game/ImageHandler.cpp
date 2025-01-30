#include "ImageHandler.h"

#include "TextureManager.h"

ImageHandler::ImageHandler(const char* fileName, int x, int y)
{
	mPositionX = x;
	mPositionY = y;
	m_transform.x = x;
	m_transform.y = y;
	m_transform.w = 32;
	m_transform.h = 32;
	mSpeed = 0;

	//m_pTexture = TextureManager::LoadTexture(fileName);
}

ImageHandler::~ImageHandler()
{
	SDL_DestroyTexture(m_pTexture);
}

void ImageHandler::Renderer()
{
	SDL_RenderCopy(SDL_Game::m_pRenderer, m_pTexture, nullptr, &m_transform);
}

void ImageHandler::Update(double deltaTime)
{
}
