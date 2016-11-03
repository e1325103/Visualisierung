#pragma once
#include "SeedGenerator.h"
#include <vector>
#include <algorithm>
#include <map>

class EvenSpacedSeedGenerator : public SeedGenerator
{
public:
	EvenSpacedSeedGenerator(int _width, int _height, int _distance);
	~EvenSpacedSeedGenerator();

	Vector2 getNextPoint();
	void start();
	bool update(Vector2 point);
	bool isFinished();
private:
	std::map<int, std::list<Vector2>*> map;
	std::list<Vector2> currentLine;
	std::vector<Vector2> possibleSeeds;
	int distance;
	int mapWidth;
	int mapHeight;
	int count;

	bool EvenSpacedSeedGenerator::checkNeighborhood(Vector2 point);
	bool EvenSpacedSeedGenerator::checkNeighbor(Vector2 point, int index);
};