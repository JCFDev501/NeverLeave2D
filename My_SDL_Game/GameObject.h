#pragma once

#include <SDL.h>
#include <string>

#include "Direction.h"
#include "Vector2.h"


class Collider;

class GameObject
{
	
protected:
	// ToDo Make this cleaner
	Direction mCurrentDirection = { 0, 0 };
	Direction mRight = { 1, 0 };
	Direction mLeft = { -1, 0 };
	Direction mUp = { 0, 1 };
	Direction mDown = { 0, -1 };
	Direction mUpRight = { 1, 1 };
	Direction mDownRight = { -1, -1 };
	Direction mUpLeft = { 1, -1 };
	Direction mDownLeft = { -1, 1 };

	// The name of our game object 
	std::string mName = "No Name";
	std::string mType = "UnKnown";

	// Pixels per second
	double mSpeed = 0;
	
	bool mActive = true;

	SDL_Color m_color{};

	SDL_Texture* m_pTexture = nullptr;

	

	// Horizontal position
	double m_x = 0;

	// Vertical position
	double m_y = 0;

public:
	SDL_Rect m_transform{};

	virtual ~GameObject() = default;

	// Gets called by the main loop each frame to update this objects state.
	virtual void Update(double deltaTime) {}

	// Gets called by the main loop each frame to render this object.
	virtual void Renderer() {}

	// Callback for when a collision occurs
	virtual void OnCollision(Collider* pCollider) {}

	// Handles this event in the context of this object.
	virtual void HandleEvent(SDL_Event* pEvent) {}

	// Attempts to move the object and returns whether it succeeded.
	virtual std::string Move(Vector2<float> direction, float speedMultiplier) { return ""; }

	//Gets this objects Position
	virtual Vector2<float> GetPosition() { return Vector2<float>{static_cast<float>(m_x), static_cast<float>(m_y)}; }


	// Getters and Setters for directions
	void SetDirection(int x, int y) { mCurrentDirection.x = x, mCurrentDirection.y = y; }

	// Getters and Setters
	void SetSpeed(const double& speed) { mSpeed = speed; }
	std::string GetName() { return mName; }
	std::string GetType() { return mType; }
	[[nodiscard]] double GetX() const { return m_x; }
	[[nodiscard]] double GetY() const { return m_y; }
	void setX(double value) { m_x = value; }
	void setY(double value) { m_y = value; }
	[[nodiscard]] double GetSpeed() const { return mSpeed; }
	[[nodiscard]] Direction GetDirection() const { return mCurrentDirection; }
	bool GetActive() { return mActive; }
	void SetActive(bool value) { mActive = value; }
	
};


