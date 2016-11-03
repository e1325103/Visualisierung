#include "RandomSeedGenerator.h"

RandomSeedGenerator::RandomSeedGenerator(int _width, int _height, int _count) : SeedGenerator(_width, _height), count(_count), current(0)
{
	srand(time(NULL));
}

RandomSeedGenerator::~RandomSeedGenerator()
{
}

Vector2 RandomSeedGenerator::getNextPoint() {
	current++;
	float x = 0 + (rand() % (int)(SeedGenerator::width));
	float y = 0 + (rand() % (int)(SeedGenerator::height));
	return Vector2(x, y);
}

void RandomSeedGenerator::start() {
	current = 0;
}

bool RandomSeedGenerator::update(Vector2 point) {
	return true;
}

bool RandomSeedGenerator::isFinished() {
	return current >= count;
}