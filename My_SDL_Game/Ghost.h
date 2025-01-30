#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "Collider.h"
#include "ParticleSystem.h"


class Ghost : public GameObject
{
	static constexpr int k_pShapeColor[] = { 0, 255, 0, SDL_ALPHA_OPAQUE };

	// Width
	static constexpr int s_width = 64;

	// Length
	static constexpr int s_length = 64;

	// Stamina
	double mStamina;

	Animator m_Movement;

	// collider component for checking
	Collider m_collider;
	Collider* GetColider() { return &m_collider; }

	SDL_Rect mBoxColider{ m_Movement.GetTransform().x, m_Movement.GetTransform().y, 32, 32 };

	int mHealth = 50;
	int mili = 0;
	bool isDead = false;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;

	

public:
	Ghost(float x, float y, CollisionManager* pCollisionManager);
	~Ghost() override;
	void Update(double deltaTime) override;
	void Renderer() override;
	void OnCollision(Collider* pCollider) override;
	std::string TryMove(Vector2<float> deltaPosition);
	int GetHealth() const { return mHealth; }

	Animator GetAnimation() { return m_Movement; }

private:
	void MovementManager(double deltaTime);
	void AnimationManager();
};

