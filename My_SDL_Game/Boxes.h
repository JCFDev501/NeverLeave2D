#pragma once
#include "GameObject.h"
#include "Collider.h"

class Boxes : public GameObject
{
	int mPositionX;
	int mPositionY;

	// collider component for checking
	Collider m_collider;
public:
	Boxes(SDL_Rect transform, CollisionManager* pCollisionManager);
	~Boxes() override;
	void Renderer() override;
	void Update(double deltaTime) override;

	SDL_Texture* GetTexture() { return m_pTexture; }
};

