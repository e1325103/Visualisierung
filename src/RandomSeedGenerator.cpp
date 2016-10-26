#include "RandomSeedGenerator.h"

RandomSeedGenerator::RandomSeedGenerator(int _width, int _height, int _count) : SeedGenerator(_width, _height), count(_count), current(0)
{
}

RandomSeedGenerator::~RandomSeedGenerator()
{
}

QPoint RandomSeedGenerator::getNextPoint() {
	current++;
	float x = 0 + (rand() % (int)(SeedGenerator::width));
	float y = 0 + (rand() % (int)(SeedGenerator::height));
	return QPoint(x, y);
}

void RandomSeedGenerator::start() {
	current = 0;
}

bool RandomSeedGenerator::update(QPoint point) {
	return true;
}

bool RandomSeedGenerator::isFinished() {
	return current >= count;
}