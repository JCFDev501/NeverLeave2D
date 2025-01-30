#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "Collider.h"

class BatBoss : public GameObject
{
	using Vector2 = Vector2<float>;

	static constexpr int k_pShapeColor[] = { 0, 255, 0, SDL_ALPHA_OPAQUE };

	// Width
	static constexpr int s_width = 128;

	// Length
	static constexpr int s_length = 128;

	// Stamina
	double mStamina;

	Animator m_Movement;

	// collider component for checking
	Collider m_collider;
	Collider* GetColider() { return &m_collider; }

	SDL_Rect mBoxColider{ m_Movement.GetTransform().x, m_Movement.GetTransform().y, 50, 50 };

	int mHealth = 150;
	int mili = 0;
	bool isDead = false;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;


public:
	BatBoss(double x, double y, CollisionManager* pCollisionManager);
	~BatBoss() override;
	void Update(double deltaTime) override;
	void Renderer() override;
	void OnCollision(Collider* pCollider) override;
	std::string TryMove(Vector2 deltaPosition);
	int GetHealth() const { return mHealth; }

	Animator GetAnimation() { return m_Movement; }

private:
	void MovementManager(double deltaTime);
	void AnimationManager();
};

