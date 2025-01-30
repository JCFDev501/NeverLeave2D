#include "Gates.h"

#include "GameState.h"
#include "State.h"
#include "TextureManager.h"

Gates::Gates(GameState* pOwner, SDL_Rect scr, SDL_Rect dest, CollisionManager* pCollisionManager, const char* filename)
	:Walls(scr, dest, pCollisionManager, filename)
	,m_pOwner(pOwner)
{
	mName = "Gate";
}

void Gates::Update(double deltaTime)
{
	if (m_pOwner->GetStateCleared())
	{
		m_pTexture = TextureManager::LoadTexture("assets/Tile/GateOpened");
	}
}
