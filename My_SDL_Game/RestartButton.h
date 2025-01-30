#pragma once
#include <functional>

#include "GameObject.h"

class RestartButton : public GameObject
{
	// The function that will execute upon click
	std::function<void()> m_callback;

	// Weather button is highlighted.
	bool mIsHighlighted = false;
	bool x;
	bool y;

public:
	RestartButton(SDL_Rect transform, SDL_Renderer* pRenderer);
	~RestartButton();

	void Renderer() override;

	// Handles this event in the context of this object.
	void HandleEvent(SDL_Event* pEvent) override;

	// Executes the callback
	void Trigger();

	// Sets this buttons highlight state
	void SetHighlight(bool value) { mIsHighlighted = value; }


	// Assigns a callback function.
	void SetCallBack(std::function<void()> callback)
	{
		m_callback = callback;
	}

private:
	// Returns whether (x,y) is within the bounds of the button.
	bool HitTest(int x, int y);
};

