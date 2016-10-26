#pragma once
#include "SeedGenerator.h"
#include <vector>
#include <algorithm>

class EvenSpacedSeedGenerator : public SeedGenerator
{
public:
	EvenSpacedSeedGenerator(int _width, int _height, int _distance);
	~EvenSpacedSeedGenerator();

	QPoint getNextPoint();
	void start();
	bool update(QPoint point);
	bool isFinished();
private:
	bool** map;
	std::vector<QPoint> possibleSeeds;
	int distance;
	int count;
};