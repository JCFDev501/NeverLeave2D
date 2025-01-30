#include "PlayerCharacter.h"
#include <iostream>
#include "CollisionManager.h"
#include "TextureManager.h"


PlayerCharacter::PlayerCharacter(double x, double y, CollisionManager* pCollisionManager, SDL_Renderer* pRender)
	:mStamina(10)
	,m_Movement("assets/Animations/player_Movement_Sprite_Sheet.png", 12,64,64,32, pRender)
	,m_collider(this, mBoxColider, pCollisionManager)
	,m_pCollisionManager(pCollisionManager)
{
	mName = "Player";
	mType = "Trigger";
	m_x = x;
	m_y = y;
	m_transform.x = static_cast<int>(x);
	m_transform.y = static_cast<int>(y);
	m_transform.w = s_width;
	m_transform.h = s_length;
	mSpeed = 150.00;

	// The goal in the future would be to have every object have one sprite sheet just need to figure
	// out how the sprite sheet would be formatted:)

	//m_pTexture = TextureManager::LoadTexture("assets/Player_Idle.png");
	m_Movement.AddAnimation("idleFront", 0, 0);
	m_Movement.AddAnimation("idleBack", 4, 4);
	m_Movement.AddAnimation("idleLeft", 8, 8);
	m_Movement.AddAnimation("idleRight", 12, 12);
	m_Movement.AddAnimation("walkFront", 0, 3);
	m_Movement.AddAnimation("walkBack", 4, 7);
	m_Movement.AddAnimation("walkLeft", 8, 11);
	m_Movement.AddAnimation("walkRight", 12, 15);
	m_Movement.AddAnimation("walkDownLeft", 16, 19);
	m_Movement.AddAnimation("walkDownRight", 20, 23);
	m_Movement.AddAnimation("walkUpLeft", 24, 27);
	m_Movement.AddAnimation("walkUpRight", 28, 31);

	
	m_pSound = Mix_LoadWAV("assets/MusicAndSound/Hurt.wav");
	m_pHeal = Mix_LoadWAV("assets/MusicAndSound/Heal.wav");
	m_pCastFireBall = Mix_LoadWAV("assets/MusicAndSound/fireBallCast.wav");
	m_pCoinCollected = Mix_LoadWAV("assets/MusicAndSound/coinSound.wav");
	
	Mix_VolumeChunk(m_pSound, 20);
	Mix_VolumeChunk(m_pHeal, 20);

}

PlayerCharacter::~PlayerCharacter()
{
	SDL_DestroyTexture(m_pTexture);

	if (m_pSound != nullptr)
	{
		Mix_FreeChunk(m_pSound);
		m_pSound = nullptr;
	}
}

void PlayerCharacter::Update(double deltaTime)
{
	// updates Player direction and speed
	m_Movement.Update(deltaTime);
	AnimationManager();
	MovementManager(deltaTime);
	m_pCollisionManager->CheckForCollisionAndNotify(this->GetColider());

	if (mCastedFireBall)
		CasteFireBall(m_pCollisionManager, deltaTime);

	FireBall* toDelete;

	for (auto& fireBall : mFireBalls)
	{
		if (mFireBalls.empty())
			break;

		if (fireBall != nullptr)
			fireBall->Update(deltaTime);

		if (fireBall->GetFireBallHitTest())
		{
			toDelete = fireBall;
			std::cout << "FireBall\n";
		}
	}
	
	mFireBalls.remove(toDelete);

	if (mMana > 100)
	{
		mMana = 100;
	}
}

void PlayerCharacter::Renderer()
{
	m_Movement.Render(SDL_Game::m_pRenderer);
	m_collider.Render(SDL_Game::m_pRenderer);

	for (const auto& fireBall : mFireBalls)
	{
		fireBall->Renderer();
	}
}
//TODO I need to figure out how to have damage and heal tick on delta time and not frame time
void PlayerCharacter::OnCollision(Collider* pCollider)
{
	if(pCollider->GetOwner()->GetName() == "WinZone")
	{
		std::cout << "You Beat this Floor \n";
	}
	else if (pCollider->GetOwner()->GetName() == "Coin")
	{
		std::cout << "Detected " << pCollider->GetOwner()->GetName() << "\n";
		Mix_PlayChannel(-1, m_pCoinCollected, 0);
		mGold++;
	}
	else if(pCollider->GetOwner()->GetName() == "Key")
	{
		mKeys++;
	}
	else if (pCollider->GetOwner()->GetName() == "ManaCrystal")
	{
		mMana += 50;
	}
	else if (pCollider->GetOwner()->GetName() == "Bomb")
	{
		mBombs++;
	}
	else if (pCollider->GetOwner()->GetName() == "Gate")
	{
		std::cout << "Detected " << pCollider->GetOwner()->GetName() << "\n";
		if (mPassGate)
			mWentThroughGate = true;
	}
	else if (pCollider->GetOwner()->GetName() == "box")
	{
		std::cout << "Detected " << pCollider->GetOwner()->GetName() << "\n";
	}
	else if (pCollider->GetOwner()->GetName() == "Wall")
	{
	}
	else if (pCollider->GetOwner()->GetName() == "EvilTim")
	{
		std::cout << "Detected " << pCollider->GetOwner()->GetName() << "\n";
		mHealth = 0;
	}
	else if (pCollider->GetOwner()->GetName() == "FairyFountain")
	{
		
		Mix_PlayChannel(-1, m_pHeal, 0);
		if (mHealth > 0)
		{
			mili++;
			if (mili == 1000)
			{
				mHealth++;
				mMana++;
				mili = 0;
				if (mHealth > 100)
				{
					mHealth = 100;
				}
				else
				{
					std::cout << "Health: " << mHealth << "\n";
				}
		
			}
		
		}
	}
	else if (pCollider->GetOwner()->GetName() == "SpikedFloor")
	{
		Mix_PlayChannel(-1, m_pSound, 0);
		if (mHealth > 0)
		{
			mili++;
			if (mili == 1000)
			{
				mHealth--;
				std::cout << mHealth << "\n";
				mili = 0;
			}
		}
	}
	else if (pCollider->GetOwner()->GetName() == "Bat" || pCollider->GetOwner()->GetName() == "ZombieGuard")
	{
		mHealth = 0;
	}
}

//std::string PlayerCharacter::TryMove(Vector2 deltaPosition)
//{
//	std::string didMove = m_collider.TryMove(deltaPosition);
//
//	//if (didMove.empty())
//	//{
//	//	m_transform.x += deltaPosition.m_x;
//	//	m_transform.y += deltaPosition.m_y;
//	//}
//
//	return didMove;
//}

void PlayerCharacter::MovementManager(double deltaTime)
{
	// Change in position.
	const double deltaPosition = mSpeed * deltaTime;

	// update the transform.
	m_transform.x = static_cast<int>(m_x);
	m_transform.y = static_cast<int>(m_y);

	m_Movement.SetTransform(m_transform);

	float position_x = static_cast<float>(m_Movement.GetTransform().x + 25);
	float position_y = static_cast<float>(m_Movement.GetTransform().y + 31);
	float size_w = static_cast<float>(mBoxColider.w);
	float size_h = static_cast<float>(mBoxColider.h);

	
	m_collider.SetTransForm(Vector2{ position_x, position_y }, Vector2{ size_w, size_h });

	if (mCurrentDirection.x == mRight.x && mCurrentDirection.y == mRight.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 1, 0 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x += deltaPosition;
		}
		m_Movement.SetAnimationState("walkRight");
	}
	else if (mCurrentDirection.x == mLeft.x && mCurrentDirection.y == mLeft.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ -1, 0 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x -= deltaPosition;
		}
		m_Movement.SetAnimationState("walkLeft");
	}
	else if (mCurrentDirection.x == mUp.x && mCurrentDirection.y == mUp.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 0, -1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_y -= deltaPosition;
		}
		m_Movement.SetAnimationState("walkBack");
	}
	else if (mCurrentDirection.x == mDown.x && mCurrentDirection.y == mDown.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 0, 1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_y += deltaPosition;
		}
		m_Movement.SetAnimationState("walkFront");
	}
	else if (mCurrentDirection.x == mUpRight.x && mCurrentDirection.y == mUpRight.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 1, -1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x += deltaPosition;
			m_y -= deltaPosition;
		}
		m_Movement.SetAnimationState("walkUpRight");
	}
	else if (mCurrentDirection.x == mUpLeft.x && mCurrentDirection.y == mUpLeft.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ -1, -1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x -= deltaPosition;
			m_y -= deltaPosition;
		}
		m_Movement.SetAnimationState("walkUpLeft");

	}
	else if (mCurrentDirection.x == mDownRight.x && mCurrentDirection.y == mDownRight.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ 1, 1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x += deltaPosition;
			m_y += deltaPosition;
		}
		m_Movement.SetAnimationState("walkDownRight");
	}
	else if (mCurrentDirection.x == mDownLeft.x && mCurrentDirection.y == mDownLeft.y)
	{
		const std::string collided = m_collider.TryMove(Vector2{ -1, 1 });
		if (collided.empty() || collided == "Trigger")
		{
			m_x -= deltaPosition;
			m_y += deltaPosition;
		}
		m_Movement.SetAnimationState("walkDownLeft");
	}
	else
	{
		if (m_Movement.GetAnimationState() == "walkFront")
		{
			m_Movement.SetAnimationState("idleFront");
		}
		else if (m_Movement.GetAnimationState() == "walkBack")
		{
			m_Movement.SetAnimationState("idleBack");
		}
		else if (m_Movement.GetAnimationState() == "walkLeft")
		{
			m_Movement.SetAnimationState("idleLeft");
		}
		else if (m_Movement.GetAnimationState() == "walkRight")
		{
			m_Movement.SetAnimationState("idleRight");
		}
		else if (m_Movement.GetAnimationState() == "walkDownLeft" || m_Movement.GetAnimationState() == "walkDownRight")
		{
			m_Movement.SetAnimationState("idleFront");
		}
		else if (m_Movement.GetAnimationState() == "walkUpLeft" || m_Movement.GetAnimationState() == "walkUpRight")
		{
			m_Movement.SetAnimationState("idleBack");
		}
		
	}
}

void PlayerCharacter::AnimationManager()
{
	m_Movement.GetAnimationState();


	if (m_Movement.GetAnimationState() == "idleFront")
	{
		m_Movement.PlayAnimation("idleFront");
	}
	else if (m_Movement.GetAnimationState() == "idleBack")
	{
		m_Movement.PlayAnimation("idleBack");
	}
	else if (m_Movement.GetAnimationState() == "idleLeft")
	{
		m_Movement.PlayAnimation("idleLeft");
	}
	else if (m_Movement.GetAnimationState() == "idleRight")
	{
		m_Movement.PlayAnimation("idleRight");
	}
	else if (m_Movement.GetAnimationState() == "walkFront")
	{
		m_Movement.PlayAnimation("walkFront");
	}
	else if (m_Movement.GetAnimationState() == "walkBack")
	{
		m_Movement.PlayAnimation("walkBack");
	}
	else if (m_Movement.GetAnimationState() == "walkLeft")
	{
		m_Movement.PlayAnimation("walkLeft");
	}
	else if (m_Movement.GetAnimationState() == "walkRight")
	{
		m_Movement.PlayAnimation("walkRight");
	}
	else if (m_Movement.GetAnimationState() == "walkDownLeft")
	{
		m_Movement.PlayAnimation("walkDownLeft");
	}
	else if (m_Movement.GetAnimationState() == "walkDownRight")
	{
		m_Movement.PlayAnimation("walkDownRight");
	}
	else if (m_Movement.GetAnimationState() == "walkUpLeft")
	{
		m_Movement.PlayAnimation("walkUpLeft");
	}
	else if (m_Movement.GetAnimationState() == "walkUpRight")
	{
		m_Movement.PlayAnimation("walkUpRight");
	}

}

void PlayerCharacter::CasteFireBall(CollisionManager* pCollisionManager, double deltaTime)
{
	if (mMana >= 5)
	{
		if (m_Movement.GetAnimationState() == "walkRight" || m_Movement.GetAnimationState() == "idleRight")
		{
			Shoot(1, 0, m_transform.x+ 52,
				m_transform.y + 43, pCollisionManager);
		}
		else if (m_Movement.GetAnimationState() == "walkLeft" || m_Movement.GetAnimationState() == "idleLeft")
		{
			Shoot(-1, 0, m_transform.x  - 10,
				m_transform.y + 43, pCollisionManager);
		}
		else if (m_Movement.GetAnimationState() == "walkBack" || m_Movement.GetAnimationState() == "idleBack")
		{
			Shoot(0, 1, m_transform.x + 20,
				m_transform.y - 20, pCollisionManager);
		}
		else if (m_Movement.GetAnimationState() == "walkFront" || m_Movement.GetAnimationState() == "idleFront")
		{
			Shoot(0, -1, m_transform.x + 20,
				m_transform.y + 63, pCollisionManager);
		}
		else if (m_Movement.GetAnimationState() == "walkUpRight")
		{
			Shoot(1, 1, m_transform.x + 25,
				m_transform.y + 63, pCollisionManager);
		}
		else if (m_Movement.GetAnimationState() == "walkUpLeft")
		{
			Shoot(1, -1, m_transform.x + 25,
				m_transform.y + 63, pCollisionManager);
		}
		else if (m_Movement.GetAnimationState() == "walkDownRight")
		{
			Shoot(-1, -1, m_transform.x + 25,
				m_transform.y + 63, pCollisionManager);
		}
		else if (m_Movement.GetAnimationState() == "walkDownLeft")
		{
			Shoot(-1, 1, m_transform.x + 25,
				m_transform.y + 63, pCollisionManager);
		}
	}

	//if (mMana == 0)
	//{
		// recharge mama
	//}

	mCastedFireBall = false;
}

void PlayerCharacter::Shoot(int direction_X, int direction_Y, int position_X, int position_Y, CollisionManager* pCollisionManager)
{
	mMana -= 1;
	Mix_PlayChannel(-1, m_pCastFireBall, 0);
	auto toShoot = new FireBall(pCollisionManager,	position_X, position_Y);
	toShoot->SetDirection(direction_X, direction_Y);
	toShoot->m_transform.h = 20;
	toShoot->m_transform.w = 20;
	mFireBalls.emplace_front(toShoot);
}
