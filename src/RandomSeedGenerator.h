#pragma once
#include "SeedGenerator.h"

class RandomSeedGenerator : public SeedGenerator
{
public:
	RandomSeedGenerator(int _width, int _height, int _count);
	~RandomSeedGenerator();

	QPoint getNextPoint();
	void start();
	bool update(QPoint point);
	bool isFinished();
private:
	int count;
	int current;
};