#pragma once
#include "SeedGenerator.h"
#include <queue>
#include <map>

class EvenSpacedSeedGenerator : public SeedGenerator
{
public:
	EvenSpacedSeedGenerator(int _width, int _height, int _distance, float _startRel, float _stopRel);
	~EvenSpacedSeedGenerator();

	Vector2 getNextPoint();
	void start();
	bool update(Vector2 point);
	bool isFinished();
private:
	std::map<int, std::list<Vector2>*> map;
	std::queue<std::list<Vector2>*> lines;
	std::list<Vector2>* buildLine;
	std::queue<Vector2> seedPoints;
	Vector2 lastAddedPoint;
	int distance;
	float startRel;
	float stopRel;
	int mapWidth;
	int mapHeight;
	bool finished;

	bool EvenSpacedSeedGenerator::checkNeighborhood(Vector2 point);
	bool EvenSpacedSeedGenerator::checkNeighbor(Vector2 point, int index);
};