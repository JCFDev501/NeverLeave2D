#pragma once
#include "Animator.h"
#include "GameObject.h"
#include "Collider.h"

class GuardZombie : public GameObject
{
	using Vector2f = Vector2<float>;
	GameObject* m_pTarget;
	const float m_kDetectDistanceSqr;

	const float m_kSpeed;

	Vector2f m_Position;
	Vector2f m_size;

	Collider m_Collider;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;

	Animator m_Fly;

	int mHealth = 100;
public:

	GuardZombie(Vector2f position, Vector2f size, GameObject* pTarget, CollisionManager* pCollisionManager,
		float speed = 100, float detectionRadius = 600);
	~GuardZombie() override;

	Vector2<float> GetPosition() override { return m_Position; }

	void Update(double deltaTime) override;

	void Renderer() override;

	void OnCollision(Collider* pCollider) override;

	std::string Move(Vector2<float> direction, float speedMultiplier) override;

	int GetHealth() { return mHealth; }
};

