#include "TileMap.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

#include "Chest.h"
#include "CollisionManager.h"
#include "Floor.h"
#include "Gates.h"
#include "TextureManager.h"
#include "Walls.h"


TileMap::TileMap(GameState* pOwner, CollisionManager* pCollisionManager, std::string levelFileName)
	:m_pTile(nullptr)
	,m_pCollisionManager(pCollisionManager)
	,m_pOwner(pOwner)
{

	mSrc.x = 0;
	mSrc.y = 0;
	mSrc.h = 32;
	mSrc.w = 32;

	mDest.w = mSrc.w;
	mDest.h = mSrc.h;

	mDest.y = 0;
	mDest.x = 0;
	m_pTile = new Tile{ mSrc, mDest};

	create_map(levelFileName);

	load_map(pCollisionManager, mLevel);
}

TileMap::~TileMap()
{
	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col < 30; col++)
		{
			delete mMap[row][col];
		}
	}
}

void TileMap::create_map(std::string levelFileName)
{
	std::ifstream levelFile(levelFileName, std::ios::in);
	// asserts that file is Open
	assert(levelFile.is_open());
	std::string word;

	// Gets Line
	getline(levelFile, word);

	int j = 0;

	// returns true if and when the end of the file was reached on the previous read attempt
	while (!levelFile.eof())   
	{
		int k = 0;
		// Loops through each line
		for (int i = 0; i < word.size(); i++)
		{
			// if Line start with '#' skip it and get Next line
			if (word[i] == '#')
			{
				j--;
				break;
			}

			if (word[i] == '0')
			{
				mLevel[j][k] = 0;
			}
			else if (word[i] == '1')
			{
				if ( i + 1 < word.size() && word[i + 1] == ',')
				{
					mLevel[j][k] = 1;
					i++;
					k++;
					continue;
				}

				i++;

				if (word[i] == '0')
				{
					mLevel[j][k] = 10;
				}
				else if (word[i] == '1')
				{
					mLevel[j][k] = 11;
				}
				else if (word[i] == '2')
				{
					mLevel[j][k] = 12;
				}
				else if (word[i] == '3')
				{
					mLevel[j][k] = 13;
				}
				else if (word[i] == '4')
				{
					mLevel[j][k] = 14;
				}
				else if (word[i] == '5')
				{
					mLevel[j][k] = 15;
				}
				else if (word[i] == '6')
				{
					mLevel[j][k] = 16;
				}
				else if (word[i] == '7')
				{
					mLevel[j][k] = 17;
				}
				else if (word[i] == '8')
				{
					mLevel[j][k] = 18;
				}
				else if (word[i] == '9')
				{
					mLevel[j][k] = 19;
				}
			}
			else if (word[i] == '2')
			{
				if (i + 1 < word.size() && word[i + 1] == ',')
				{
					mLevel[j][k] = 2;
					i++;
					k++;
					continue;
				}

				i++;

				if (word[i] == '0')
				{
					mLevel[j][k] = 20;
				}
				else if (word[i] == '1')
				{
					mLevel[j][k] = 21;
				}
				else if (word[i] == '2')
				{
					mLevel[j][k] = 22;
				}
				else if (word[i] == '3')
				{
					mLevel[j][k] = 23;
				}
				else if (word[i] == '4')
				{
					mLevel[j][k] = 24;
				}
				else if (word[i] == '5')
				{
					mLevel[j][k] = 25;
				}
				else if (word[i] == '6')
				{
					mLevel[j][k] = 26;
				}
				else if (word[i] == '7')
				{
					mLevel[j][k] = 27;
				}
				else if (word[i] == '8')
				{
					mLevel[j][k] = 28;
				}
				else if (word[i] == '9')
				{
					mLevel[j][k] = 29;
				}
			}
			else if (word[i] == '3')
			{
				mLevel[j][k] = 3;
			}
			else if (word[i] == '4')
			{
				mLevel[j][k] = 4;
			}
			else if (word[i] == '5')
			{
				mLevel[j][k] = 5;
			}
			else if (word[i] == '6')
			{
				mLevel[j][k] = 6;
			}
			else if (word[i] == '7')
			{
				mLevel[j][k] = 7;
			}
			else if (word[i] == '8')
			{
				mLevel[j][k] = 8;
			}
			else if (word[i] == '9')
			{
				mLevel[j][k] = 9;
			}
			
			i++;
			k++;
		}
		j++;
		std::getline(levelFile, word);         // try to grab another
	}

	// Closes file
	levelFile.close();
}

void TileMap::load_map(CollisionManager* pCollisionManager, int alevel[16][30])
{
	int type = 0;

	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col < 30; col++)
		{
			type = alevel[row][col];

			mDest.x = col * 32;
			mDest.y = row * 32 + 96;

			switch (type)
			{
			case 0:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/ConnerTileLeft.png");
				break;

			case 1:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/TopTile.png");
				break;

			case 2:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/ConnerTileRight.png");
				break;

			case 3:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/RightTile.png");
				break;
				
			case 4:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/BottomConnerRight.png");
				break;
			case 5:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/BottomTile.png");
				break;

			case 6:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/BottomConnerLeft.png");
				break;

			case 7:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/LeftTile.png");
				break;
			case 8:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/ConnerFTileLeft.png");
				break;

			case 9:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/TopFTile.png");
				break;

			case 10:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/ConnerFTileRight.png");
				break;

			case 11:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/RightFTile.png");
				break;

			case 12:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/BottomConnerFRight.png");
				break;

			case 13:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/BottomFTile.png");
				break;

			case 14:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/BottomConnerFLeft.png");
				break;

			case 15:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/LeftFTile.png");
				break;

			case 16:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/Floor.png");
				break;

			case 17:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/RightCornerHole.png");
				break;

			case 18:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/TopHole.png");
				break;

			case 19:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/LeftConnerHole.png");
				break;

			case 20:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/RightHole.png");
				break;

			case 21:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/BottomRightConnerHole.png");
				break;

			case 22:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/BottomHole.png");
				break;

			case 23:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/BottomLeftConnerHole.png");
				break;

			case 24:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/LeftHole.png");
				break;

			case 25:
				mMap[row][col] = new Floor(mSrc, mDest, "assets/Tiles/Hole.png");
				break;

			case 26:
				mMap[row][col] = new Walls(mSrc, mDest, m_pCollisionManager, "assets/Tiles/Block.png");
				break;

			case 27:
				mMap[row][col] = new Chest(mSrc, mDest, m_pCollisionManager);
				break;
			case 28:
				mMap[row][col] = new Gates(m_pOwner ,mSrc, mDest, m_pCollisionManager, "assets/Tiles/Gate.png");
				break;
			case 29:
				mMap[row][col] = new Gates(m_pOwner, mSrc, mDest, m_pCollisionManager, "assets/Tiles/GateDown.png");
				break;
			}
		}
	}
}

void TileMap::Renderer()
{
	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col < 30; col++)
		{

			mDest.x = col * 32;
			mDest.y = row * 32 + 96;

			mMap[row][col]->Draw(mSrc, mDest);
			mMap[row][col]->Renderer();


			SDL_SetRenderDrawColor(SDL_Game::m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		}
	}
}

void TileMap::Update(double deltaTime)
{
	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col < 30; col++)
		{

			mMap[row][col]->Update(deltaTime);

		}
	}
}
