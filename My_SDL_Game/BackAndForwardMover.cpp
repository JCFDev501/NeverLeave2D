#include "BackAndForwardMover.h"

#include <iostream>

#include "SDL_Game.h"

BackAndForwardMover::BackAndForwardMover(double x, double y)
	:m_x(x)
	,m_y(y)
	,m_currentOffset(0)
	,m_direction(1)
{
	m_transform.x = static_cast<int>(x);
	m_transform.y = static_cast<int>(y);
	m_transform.w = s_width;
	m_transform.h = s_length;
}

BackAndForwardMover::~BackAndForwardMover()
= default;

void BackAndForwardMover::Update(double deltaTime)
{
	// Change in position.
	const double deltaPosition = s_kSpeed * deltaTime;

	m_currentOffset += deltaPosition; // update or journey progress
	m_x += deltaPosition; // updates position by moving in current CurrentDirection
	
	// update the transform.
	m_transform.x = static_cast<int>(m_x);
	
	if (m_currentOffset >= 200)
	{
		m_direction *= -1;
		m_currentOffset = 0;
	}

	std::cout << m_x << std::endl;
}

void BackAndForwardMover::Renderer()
{
	// Setting color
	SDL_SetRenderDrawColor(
		SDL_Game::m_pRenderer,
		k_pShapeColor[0],
		k_pShapeColor[1],
		k_pShapeColor[2],
		k_pShapeColor[3]);

	// Draw Rectangle
	SDL_RenderFillRect(SDL_Game::m_pRenderer, &m_transform);
}
