#pragma once

#include <SDL_mixer.h>

#include "GameObject.h"
#include "Collider.h"

class Switch : public GameObject
{
	Collider mcollider;

	int mPositionX;
	int mPositionY;
	bool mFlipped = false;

	SDL_Rect mBoxColider{ 16, 16, 16, 16 };

	// sound data.
	Mix_Chunk* m_pSound;

	// ID of the currently playing sound channel.
	// Resets to -1 if no channel is playing.
	int m_activeSoundChannel;

public:
	Switch(SDL_Rect transform, CollisionManager* pCollisionManager);
	~Switch() override;
	void Update(double deltaTime) override;
	void Renderer() override;
	void OnCollision(Collider* pCollider) override;
	bool GetFlipped() const { return mFlipped; }
};

