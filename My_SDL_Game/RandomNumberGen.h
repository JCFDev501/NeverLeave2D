#pragma once
#include <random>
#include <iostream>
template<typename tType>
class RandomNumberGen // Random Number Gen
{
	std::mt19937 mEngine;

	std::random_device mRandomDevice;

	unsigned int mSeed;

	tType mRange_min;
	tType mRange_max;

public:

	RandomNumberGen(unsigned int seed, tType range_x, tType range_y);
	RandomNumberGen(tType range_x, tType range_y);
	int GetRandomNumberInt();
	float GetRandomNumberFloat();
};

template <typename tType>
RandomNumberGen<tType>::RandomNumberGen(unsigned seed, tType range_min, tType range_max)
	:mRange_min(range_min)
	, mRange_max(range_max)
{
	mEngine.seed(seed);
}

template <typename tType>
RandomNumberGen<tType>::RandomNumberGen(tType range_min, tType range_max)
	:mRange_min(range_min)
	, mRange_max(range_max)
{
	mSeed = mRandomDevice();

	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	std::cout << mSeed << std::endl;
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;

	mEngine.seed(mSeed);
}

template <typename tType>
int RandomNumberGen<tType>::GetRandomNumberInt()
{
	std::uniform_int_distribution<tType> distribution(mRange_min, mRange_max);

	tType randomNumber = distribution(mEngine);

	return randomNumber;
}

template <typename tType>
float RandomNumberGen<tType>::GetRandomNumberFloat()
{
	std::uniform_real_distribution<tType> distribution(mRange_min, mRange_max);

	tType randomNumber = distribution(mEngine);

	return randomNumber;
}
