#pragma once

#include <list>
#include <SDL_mixer.h>

#include "Animator.h"
#include "GameObject.h"
#include "Collider.h"
#include "FireBall.h"

class PlayerCharacter : public GameObject
{
	using Vector2 = Vector2<float>;

	// Shape color
	static constexpr int k_pShapeColor[] = { 0, 255, 0, SDL_ALPHA_OPAQUE };

	// Width
	static constexpr int s_width = 64;

	// Length
	static constexpr int s_length = 64;

	// Stamina
	double mStamina;

	Animator m_Movement;

	// collider component for checking
	Collider m_collider;

	Collider* GetColider() { return &m_collider; }

	SDL_Rect mBoxColider{ m_Movement.GetTransform().x, m_Movement.GetTransform().y, 16, 16 };
	int mili = 0;

	// Pointer to manager for registering and collision checking
	CollisionManager* m_pCollisionManager;

	// sound data.
	Mix_Chunk* m_pSound;

	Mix_Chunk* m_pHeal;

	Mix_Chunk* m_pCastFireBall;

	Mix_Chunk* m_pCoinCollected;

	std::list<FireBall*> mFireBalls;

	void MovementManager(double deltaTime);
	void AnimationManager();

public:
	PlayerCharacter(double x, double y, CollisionManager* pCollisionManager, SDL_Renderer* pRender);
	~PlayerCharacter() override;
	void Update(double deltaTime) override;
	void Renderer() override;
	void OnCollision(Collider* pCollider) override;
	std::string TryMove(Vector2 deltaPosition);
	

	Animator GetAnimation() { return m_Movement; }
	

	// PLAYER STATS / Abilites.
private:
	int mHealth = 100;
	int mMana = 100;
	int mGold = 0;
	int mKeys = 0;
	int mBombs = 0;
	bool mPassGate = false;
	bool mWentThroughGate = false;
public:
	[[nodiscard]] int GetHealth() const { return mHealth; }
	[[nodiscard]] int GetMana() const { return mMana; }
	[[nodiscard]] int GetGold() const { return mGold; }
	[[nodiscard]] int GetKeys() const { return mKeys; }
	[[nodiscard]] int GetBombs() const { return mBombs; }
	[[nodiscard]] int GetPassGate() const { return mPassGate; }

	void SetHealth(int value) {mHealth = value; }
	void SetMana(int value)  { mMana = value; }
	void SetGold(int value)  { mGold = value; }
	void SetKeys(int value)  { mKeys = value; }
	void SetBombs(int value) { mBombs = value; }

	void CasteFireBall(CollisionManager* pCollisionManager, double deltaTime);
	bool mCastedFireBall = false;

	void SetPassGate(bool value) {mPassGate = value; }
	void SetWentThroughGate(bool value) {mWentThroughGate = value; }
	bool GetWentThroughGate() const {return mWentThroughGate; }
	

private:
	void Shoot(int direction_X, int direction_Y, int position_X, int position_Y, CollisionManager* pCollisionManager);
};


// Todo Add the Rest of MovementManager Ability
// Todo Clean up Code (Update)

