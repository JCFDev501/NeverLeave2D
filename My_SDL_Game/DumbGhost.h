#pragma once
#include "AiStateMachine.h"
#include "Animator.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "ParticleSystem.h"


class DumbGhost : public GameObject
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

	AiStateMachine m_stateMachine;

	Animator m_Float;

public:
	DumbGhost(Vector2f position, Vector2f size, GameObject* pTarget, CollisionManager* pCollisionManager,
		float speed = 110, float detectionRadius = 900);
	~DumbGhost() override;

	void Update(double deltaTime) override;

	void Renderer() override;

	void OnCollision(Collider* pCollider) override;

	std::string Move(Vector2<float> direction, float speedMultiplier) override;

private:
	int mHealth = 50;
public:
	int GetHealth() { return mHealth; }
	void SetHealth(int value) { mHealth = value; }

};

