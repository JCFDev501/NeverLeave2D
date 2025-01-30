#pragma once
#include "GameObject.h"

class ImageHandler : public GameObject
{

	int mPositionX;
	int mPositionY;

public:
	ImageHandler(const char* fileName, int x, int y);

	~ImageHandler();

	void Renderer() override;
	void Update(double deltaTime) override;
};

