#pragma once
#include "GameObject.h"

class ParticleSystem : public GameObject
{
	// An individual particle
	struct Particle
	{
		Vector2<float> m_positionOffset;
		Vector2<float> m_velocity;
	};

	// Particle color
	struct particleColor
	{
		Uint8 r = 0;
		Uint8 g = 0;
		Uint8 b = 0;
		Uint8 a = 0;
	};

	// Particle Size
	Vector2<int> mSize;

	// Particle source center point.
	const Vector2<float> m_kCenterPoint;

	// number of particles in this instance.
	const int m_kParticleCount;

	// Square of the maximum distance particles can travel before resetting.
	const float m_kRadiusSqr;

	// Array of particles.
	Particle* m_pParticles;

	// Particle color
	particleColor mParticleColor;


public:
	ParticleSystem(Vector2<float> centerPoint, int particleCount, float maxSpeed, float radius, Uint8 r,
		Uint8 g, Uint8 b, Uint8 a, Vector2<int> size);
	~ParticleSystem() override;

	Vector2<float> GetPosition() override { return m_kCenterPoint; }

	void Update(double deltaTime) override;

	void Renderer() override;
};

