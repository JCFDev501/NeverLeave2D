#pragma once
#include <list>

#include "Animator.h"
#include "GameObject.h"
#include "Collider.h"


class PlayerCharacter;

class FireBall : public GameObject
{
	using  Vector2 = Vector2<float>;
	Animator mSpin;
	Collider m_collider;

	double x;
	double y;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;

	SDL_Rect mBoxColider{ m_transform.x, m_transform.y, 10, 10 };
	bool mFireBallHitTest = false;

public:
	FireBall(CollisionManager* pCollisionManager, double x, double y);
	~FireBall() override;
	
	void Update(double deltaTime) override;
	void Renderer() override;
	void OnCollision(Collider* pCollider) override;
	void MovementManager(double deltaTime);
	bool GetFireBallHitTest() { return mFireBallHitTest; }

	void Position(double position_x, double position_y)
	{
		x = position_x;
		y = position_y;
	}
};


