#include "Ui.h"

#include "PlayerCharacter.h"
#include "SDL_Game.h"
#include "UITextField.h"


Ui::Ui(SDL_Rect transform, SDL_Renderer* pRenderer, PlayerCharacter* pPlayer, TTF_Font* pFont)
	:m_pPlayer(pPlayer)
	,mUiBackground(transform, "assets/UI.png", SDL_Game::m_pRenderer)
	,m_pFont(pFont)
{
	m_transform = transform;
}

Ui::~Ui()
= default;

void Ui::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Ui::Renderer()
{
	mUiBackground.Renderer();

	const SDL_Rect health{ m_transform.x + 32 * 26, m_transform.y + 32, m_pPlayer->GetHealth(), 13 };
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(SDL_Game::m_pRenderer, &health);

	const SDL_Rect mana{ m_transform.x + 32 * 26, m_transform.y + 64, m_pPlayer->GetMana(), 13 };
	SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(SDL_Game::m_pRenderer, &mana);

	int count = m_pPlayer->GetGold();
	std::string t = std::to_string(count);
	char const* goldCount = t.c_str();
	UITextField Gold(m_pFont, goldCount, SDL_Color{ 255,255,255, SDL_ALPHA_OPAQUE },
		Vector2{ m_transform.x + 32 * 14, m_transform.y + 16, }, SDL_Game::m_pRenderer);

	Gold.Renderer();

	int count2 = m_pPlayer->GetKeys();
	std::string k = std::to_string(count2);
	char const* keyCount = k.c_str();
	UITextField Keys(m_pFont, keyCount, SDL_Color{ 255,255,255, SDL_ALPHA_OPAQUE },
		Vector2{ m_transform.x + 32 * 14, m_transform.y + 32 + 8, }, SDL_Game::m_pRenderer);

	Keys.Renderer();

	int count3 = m_pPlayer->GetBombs();
	std::string j = std::to_string(count3);
	char const* bombCount = j.c_str();
	UITextField Bomb(m_pFont, bombCount, SDL_Color{ 255,255,255, SDL_ALPHA_OPAQUE },
		Vector2{ m_transform.x + 32 * 14, m_transform.y + 64 + 2, }, SDL_Game::m_pRenderer);

	Bomb.Renderer();

	SDL_RenderPresent(SDL_Game::m_pRenderer);

}
