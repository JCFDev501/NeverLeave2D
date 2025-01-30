#include "CollidableStaticObject.h"

#include "SDL_Game.h"


CollidableStaticObject::CollidableStaticObject(double x, double y,  CollisionManager* pCollisionManager)
	:m_collider(this, m_transform, pCollisionManager)
{
	mName = "Broken";
	m_transform.x = static_cast<int>(x);
	m_transform.y = static_cast<int>(y);
	m_transform.w = 16;
	m_transform.h = 16;
}

CollidableStaticObject::~CollidableStaticObject()
{
}

void CollidableStaticObject::Update(double deltaTime)
{
	// tbd
}

void CollidableStaticObject::Renderer()
{
	TextureManager::LoadTexture("assets/dungeon_box.png");
}
