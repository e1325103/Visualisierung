#include "EvenSpacedSeedGenerator.h"
#include <iostream>

EvenSpacedSeedGenerator::EvenSpacedSeedGenerator(int _width, int _height, int _distance) : SeedGenerator(_width, _height), distance(_distance)
{
	int mapHeight = SeedGenerator::height / distance;
	int mapWidth = SeedGenerator::width / distance;
	count = 0;
	map = new bool*[mapHeight];
	for (int i = 0; i < mapHeight; i++) {
		map[i] = new bool[mapWidth];
		for (int j = 0; j < mapWidth; j++) {
			possibleSeeds.push_back(QPoint(j, i));
			count++;
		}
	}
}

EvenSpacedSeedGenerator::~EvenSpacedSeedGenerator()
{
}

QPoint EvenSpacedSeedGenerator::getNextPoint() {
	int pos = 0 + (rand() % count);
	QPoint point = possibleSeeds.at(pos);
	int x = point.x() * distance;
	int y = point.y() * distance;
	possibleSeeds.erase(possibleSeeds.begin() + pos);
	count--;
	return QPoint(x, y);
}

void EvenSpacedSeedGenerator::start() {
}

bool EvenSpacedSeedGenerator::update(QPoint point) {
	point = point / distance;
	if (!(point.x() < 0 || point.y() < 0 || (point.x() + 1) >= SeedGenerator::width / distance || (point.y() + 1) >= SeedGenerator::height / distance)) {
		if (map[point.y()][point.x()]) {
			map[point.y()][point.x()] = false;
			possibleSeeds.erase(std::remove(possibleSeeds.begin(), possibleSeeds.end(), point), possibleSeeds.end());
			count--;
			return true;
		}
	}
	return false;
}

bool EvenSpacedSeedGenerator::isFinished() {
	return count <= 0;
}