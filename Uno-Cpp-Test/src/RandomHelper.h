#pragma once

#include<vector>
#include<algorithm>
#include<random>

class RandomHelper
{
private:
	RandomHelper() = delete;
	~RandomHelper() = delete;

public:
	static void Initialize()
	{
		std::srand(std::time(0));

	}

	template <typename T> 
	static void SuffleVector(std::vector<T>& Vector)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::shuffle(Vector.begin(), Vector.end(), randomDevice);
	}

	static int GetRandomNumber(const int Max)
	{
		return std::rand() % Max;
	}

	static int GetRandomNumber(const int Min, const int Max)
	{
		return Min + (std::rand() % (Max - Min + 1));
	}
};