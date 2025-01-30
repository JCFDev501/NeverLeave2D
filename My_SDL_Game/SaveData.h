#pragma once
#include "TileMap.h"
#include "Vector2.h"
#include "GameState.h"
#include "CollisionManager.h"

class SaveData
{
public:

	
	struct Timer
	{
		int mSec;
		int mMin;
		int mHour;
	};

	// The data that we are saving.
	struct Data
	{
		// Player
		Vector2<double> mPlayerPosition;
		int mPlayerGold;
		int mPlayerMana;
		int mPlayerBombs;
		int mPlayerHealth;
		int mPlayerKeys;

		bool mPlayerCanPass;
		bool mStateCleared;

		// Coins
		int mNumberOfCoins;

		// bats
		int mNumberOfBats;

		// Ghost
		int mNumberOfGhost;

		// CurrentState
		int mState;

		// current duration of playtime
		Timer mTime;

		// Number of times Saved
		int mNumSaved;


		~Data()
		= default;
	};


private:
	// Save data folder relative location.
	static constexpr char s_kDirectory[] = "saves\\";

	// Save data file name including extension.
	static constexpr char s_kFileName[] = "savedata.save";

	// Save data file name including extension.
	static constexpr char s_kFile2Name[] = "savedata.save2";

	// Save data file name including extension.
	static constexpr char s_kFileName3[] = "savedata.save3";

	// buildFolder\saves\savedata.save


	// Whether save data has been loaded this session 
	bool m_isLoaded;

	// The actual save data that will read/written.
	Data m_data;

public:
	SaveData();
	~SaveData();

	// Attempts to save the data to disk. Returns true if did.
	bool Save();

	// AAttempts to load the data to disk. Returns true if did.
	bool Load();

	// returns if loaded
	bool GetIsLoaded() { return m_isLoaded; }

	int GetState() { return m_data.mState; }

	// Get ref to actual data
	Data& GetData() { return m_data; }
};

