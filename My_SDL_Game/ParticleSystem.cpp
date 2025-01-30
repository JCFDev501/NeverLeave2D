#include "ParticleSystem.h"

#include "RandomNumberGen.h"
#include "SDL_Game.h"

ParticleSystem::ParticleSystem(Vector2<float> centerPoint, int particleCount, float maxSpeed, float radius, Uint8 r,
	Uint8 g, Uint8 b, Uint8 a, Vector2<int> size)
	:mSize(size)
	,m_kCenterPoint(centerPoint)
	,m_kParticleCount(particleCount)
	,m_kRadiusSqr(radius * radius)
	, m_pParticles(new Particle[particleCount])
	,mParticleColor{ r, g, b, a }
{
	RandomNumberGen<float> randomNumber(-1, 1);

	for(int i = 0; i < particleCount; ++i)
	{

		// Initialize position
		m_pParticles[i].m_positionOffset = Vector2<float>{ 0,0 };

		// Randomize velocities
		m_pParticles[i].m_velocity = Vector2<float>{ randomNumber.GetRandomNumberFloat(), randomNumber.GetRandomNumberFloat() } * maxSpeed;

	}
}

ParticleSystem::~ParticleSystem()
{
	delete[] m_pParticles;
}

void ParticleSystem::Update(double deltaTime)
{

	// loop through the particle array
	for(int i = 0; i < m_kParticleCount; ++i)
	{
		// Update each particles position.
		m_pParticles[i].m_positionOffset.m_x += m_pParticles[i].m_velocity.m_x * static_cast<float>(deltaTime);
		m_pParticles[i].m_positionOffset.m_y += m_pParticles[i].m_velocity.m_y * static_cast<float>(deltaTime);

		// If the particles has exceeded the raduis, reset it.
		if(m_pParticles[i].m_positionOffset.GetSquareLength() >= m_kRadiusSqr)
		{
			m_pParticles[i].m_positionOffset = Vector2<float>{ 0,0 };
		}
	}
}

void ParticleSystem::Renderer()
{
	// Set the color
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, mParticleColor.r, mParticleColor.g, mParticleColor.b, mParticleColor.a);

	// loop through the particles
	for (int i = 0; i < m_kParticleCount; ++i)
	{
		// Get the particle position
		Particle& particle = m_pParticles[i];
		Vector2<float>& particlePosition = particle.m_positionOffset;

		// Allocate an SDL_Rect with the transformations.
		SDL_Rect particleTransform{ static_cast<int>(m_kCenterPoint.m_x + particlePosition.m_x),
		static_cast<int>(m_kCenterPoint.m_y + particlePosition.m_y), mSize.m_x, mSize.m_y };

		// Render as a rectangle.
		SDL_RenderFillRect(SDL_Game::m_pRenderer, &particleTransform);
	}
}
