#pragma once
#include "Tile.h"

class Floor : public Tile
{

public:
	Floor(SDL_Rect scr, SDL_Rect dest, const char* filename);
	~Floor() = default;
	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;
};

