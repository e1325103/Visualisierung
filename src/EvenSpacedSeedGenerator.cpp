#include "EvenSpacedSeedGenerator.h"
#include <iostream>

EvenSpacedSeedGenerator::EvenSpacedSeedGenerator(int _width, int _height, int _distance) : SeedGenerator(_width, _height), distance(_distance)
{
	count = 0;
	map = new bool*[SeedGenerator::height / distance];
	for (int i = 0; i < SeedGenerator::height / distance; i++) {
		map[i] = new bool[SeedGenerator::width / distance];
		for (int j = 0; j < SeedGenerator::width / distance; j++) {
			possibleSeeds.push_back(QPoint(j, i));
			count++;
		}
	}
}

EvenSpacedSeedGenerator::~EvenSpacedSeedGenerator()
{
}

QPoint EvenSpacedSeedGenerator::getNextPoint() {
	int pos = 0 + (rand() % (int)(count));
	QPoint point = possibleSeeds.at(pos);
	possibleSeeds.erase(possibleSeeds.begin() + pos);
	count--;
	std::cout << count << std::endl;
	return point;
}

void EvenSpacedSeedGenerator::start() {
}

bool EvenSpacedSeedGenerator::update(QPoint point) {
	point = point / distance;
	if (map[point.y()][point.x()]) {
		map[point.y()][point.x()] = false;
		possibleSeeds.erase(std::remove(possibleSeeds.begin(), possibleSeeds.end(), point), possibleSeeds.end());
		count--;
		std::cout << count << std::endl;
		return true;
	}
	return false;
}

bool EvenSpacedSeedGenerator::isFinished() {
	return count <= 0;
}