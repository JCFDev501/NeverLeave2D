#pragma once
#include <SDL_mixer.h>

#include "GuardZombie.h"
#include "AiStateMachine.h"
#include "Animator.h"

// An AI enemy that overrides Hard-codded behavior with a state machine. 
class Bat : public GameObject
{
	enum Phases
	{
		Phase1, // Boss is idle
		Phase2, // Bose Starts to chase player
		Phase3 // Boss flees from player 
	};

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

	Phases m_CurrentPhase;

	Animator m_Fly;

	// sound data.
	Mix_Chunk* m_pScream;

	//std::list<GuardZombie*> mBatBabies;

public:
	Bat(Vector2f position, Vector2f size, GameObject* pTarget, CollisionManager* pCollisionManager,
		float speed = 110, float detectionRadius = 900);
	~Bat() override;

	void Update(double deltaTime) override;

	void Renderer() override;

	void OnCollision(Collider* pCollider) override;

	std::string Move(Vector2<float> direction, float speedMultiplier) override;

private:
	int mHealth = 500;
	bool mScream = true;

public:
	int GetHealth() { return mHealth; }
	void SetHealth(int value) { mHealth = value; }
};

