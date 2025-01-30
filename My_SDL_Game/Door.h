#pragma once
#include "Collider.h"
#include "GameObject.h"
#include "Switch.h"

class Door : public GameObject
{
	Collider mCollider;

	int mPositionX;
	int mPositionY;

	SDL_Rect mBoxColider{ 16, 16, 16, 16 };

	Switch* m_pSwitch = nullptr;

	bool mOpened = false;
	bool mPassed = false;

public:
	Door(SDL_Rect transform, CollisionManager* pCollisionManager, Switch* pSwitch);
	~Door() override;
	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;

	bool GetPassed() const { return mPassed; }
};

