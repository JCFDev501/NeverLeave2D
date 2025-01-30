#pragma once
#include "GameObject.h"

class BackAndForwardMover: public GameObject 
{
private:
	// Shape color
	static constexpr int k_pShapeColor[] = { 255, 0, 255, SDL_ALPHA_OPAQUE };

	// Width
	static constexpr int s_width = 50;

	// Length
	static constexpr int s_length = 50;

	// Pixels per second
	static constexpr double s_kSpeed = 300;

	// Horizontal position
	double m_x;

	// Vertical position
	double m_y;

	// Current movement progress.
	double m_currentOffset;

	// current CurrentDirection movement, -1 for left, 1 for right
	int m_direction;

	// Transformation of the object.
	SDL_Rect m_transform;

public:
	BackAndForwardMover(double x, double y);
	~BackAndForwardMover() override;
	void Update(double deltaTime) override;
	void Renderer() override;
};

