#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "TextureManager.h"
class CollidableStaticObject : public GameObject 
{
	// collider component for checking
	Collider m_collider;

public:
	CollidableStaticObject(double x, double y, CollisionManager* pCollisionManager);

	~CollidableStaticObject();

	void Update(double deltaTime) override;

	void Renderer() override;
};

