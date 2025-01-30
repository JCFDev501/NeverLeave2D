#pragma once
#include "GameObject.h"
#include "Collider.h"

// My Tile Interface
class Tile : public GameObject
{
	
public:
	Tile(SDL_Rect scr, SDL_Rect dest);
	Tile() = default;
	~Tile() = default;

	void Renderer() override;
	void Update(double deltaTime) override;
	void OnCollision(Collider* pCollider) override;
	void Draw(SDL_Rect scr, SDL_Rect);
};

