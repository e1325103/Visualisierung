#include "EvenSpacedSeedGenerator.h"
#include <iostream>

EvenSpacedSeedGenerator::EvenSpacedSeedGenerator(int _width, int _height, int _distance, float _startRel, float _stopRel) : SeedGenerator(_width, _height), distance(_distance), startRel(_startRel), stopRel(_stopRel), finished(false)
{
	lastAddedPoint = Vector2(-1, -1);
	mapWidth = (int)ceilf((float)SeedGenerator::width / distance);
	mapHeight = (int)ceilf((float)SeedGenerator::height / distance);
	map = std::map<int, std::list<Vector2>*>();
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			map[x + y * mapWidth] = new std::list<Vector2>();
		}
	}
	buildLine = new std::list<Vector2>();
}

EvenSpacedSeedGenerator::~EvenSpacedSeedGenerator()
{

}

Vector3 EvenSpacedSeedGenerator::getNextPoint() {
	if (direction > 0.0f) {
		direction = -1.0f;
		return Vector3(lastPoint, direction);
	}
	else {
		direction = 1.0f;
	}

	if (buildLine->size() > 0) {
		lines.push(buildLine);
		for (Vector2 point : *buildLine) {
			int x = (int)(point.x() / distance);
			int y = (int)(point.y() / distance);
			map[x + y * mapWidth]->push_back(point);
		}
		buildLine = new std::list<Vector2>();
	}
	if (lines.size() > 0) {
		bool notFound = true;
		while (notFound)
		{
			while ((lines.size() > 0) && (seedPoints.size() == 0)) {
				std::list<Vector2>* currentLine = lines.front();
				lines.pop();
				Vector2 lastPoint = Vector2(-1, -1);
				for (Vector2 point : *currentLine) {
					if (lastPoint != Vector2(-1, -1) && ((point - lastPoint).magnitude() < distance)) {

						Vector2 direction = point - lastPoint;
						direction.normalise();
						direction *= (distance) * startRel;

						Vector2 seed = lastPoint + Vector2(-direction.y(), direction.x());
						if ((seed.x() >= 0) && (seed.y() >= 0) && (seed.x() < (width - 1)) && (seed.y() < (height - 1))) {
							seedPoints.push(seed);
						}
						seed = lastPoint + Vector2(direction.y(), -direction.x());
						if ((seed.x() >= 0) && (seed.y() >= 0) && (seed.x() < (width - 1)) && (seed.y() < (height - 1))) {
							seedPoints.push(seed);
						}

						if (lastPoint == currentLine->front()) {
							seed = lastPoint + Vector2(direction.x(), -direction.y());
							if ((seed.x() >= 0) && (seed.y() >= 0) && (seed.x() < (width - 1)) && (seed.y() < (height - 1))) {
								seedPoints.push(seed);
							}
							seed = lastPoint + Vector2(-direction.x(), direction.y());
							if ((seed.x() >= 0) && (seed.y() >= 0) && (seed.x() < (width - 1)) && (seed.y() < (height - 1))) {
								seedPoints.push(seed);
							}
						}

						if (point == currentLine->back()) {
							seed = point + Vector2(direction.x(), -direction.y());
							if ((seed.x() >= 0) && (seed.y() >= 0) && (seed.x() < (width - 1)) && (seed.y() < (height - 1))) {
								seedPoints.push(seed);
							}
							seed = point + Vector2(-direction.x(), direction.y());
							if ((seed.x() >= 0) && (seed.y() >= 0) && (seed.x() < (width - 1)) && (seed.y() < (height - 1))) {
								seedPoints.push(seed);
							}
						}
					}
					lastPoint = point;
				}
				delete currentLine;
			}
			while (seedPoints.size() > 0) {
				Vector2 possibleSeedPoint = seedPoints.front();
				seedPoints.pop();
				if (checkNeighborhood(possibleSeedPoint)) {
					lastPoint = possibleSeedPoint;
					return Vector3(possibleSeedPoint, direction);
				}
			}
			notFound = lines.size() > 0 && seedPoints.size() == 0;
		}
		finished = true;
	}
	else {
		float x = 0 + (rand() % (int)(SeedGenerator::width));
		float y = 0 + (rand() % (int)(SeedGenerator::height));
		lastPoint = Vector2(x, y);
		//lastPoint = Vector2((float)width / 2, (float)height / 2);
		return Vector3(lastPoint, direction);
	}
	return Vector3((float)nan(""), (float)nan(""), (float)nan(""));
}

void EvenSpacedSeedGenerator::start() {
	direction = -1.0f;
}

bool EvenSpacedSeedGenerator::update(Vector2 point) {
	if (checkNeighborhood(point)) {
		if ((lastAddedPoint == Vector2(-1, -1)) || ((point - lastAddedPoint).magnitude() >= (distance * (stopRel / 8.0f)))) {
			int x = (int)(point.x() / distance);
			int y = (int)(point.y() / distance);
			if ((x >= 0) && (y >= 0) && (x < mapWidth) && (y < mapHeight)) {
				//map[x + y * mapWidth]->push_back(point);
				buildLine->push_back(point);
				lastAddedPoint = point;
			}
		}
		return true;
	}
	return false;
}

bool EvenSpacedSeedGenerator::checkNeighborhood(Vector2 point) {
	int index = 0;
	bool result = true;
	while (index <= 8 && result) {
		result &= checkNeighbor(point, index);
		index++;
	}
	return result;
}
bool EvenSpacedSeedGenerator::checkNeighbor(Vector2 point, int index) {
	int x = (int)(point.x() / distance);
	int y = (int)(point.y() / distance);
	switch (index)
	{
	case 1:
		x--;
		y--;
		break;
	case 2:
		y--;
		break;
	case 3:
		x++;
		y--;
		break;
	case 4:
		x++;
		break;
	case 5:
		x++;
		y++;
		break;
	case 6:
		y++;
		break;
	case 7:
		x--;
		y++;
		break;
	case 8:
		x--;
		break;
	default:
		break;
	}
	if ((x >= 0) && (y >= 0) && (x < mapWidth) && (y < mapHeight)) {
		std::list<Vector2>* neighbor = map[x + y * mapWidth];
		for (Vector2 other : *neighbor) {
			Vector2 distanceToOther = other - point;
			if (distanceToOther.magnitude() < (distance * stopRel)) {
				return false;
			}
		}
	}
	return true;
}

bool EvenSpacedSeedGenerator::isFinished() {
	return finished;
}