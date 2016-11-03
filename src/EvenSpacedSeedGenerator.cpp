#include "EvenSpacedSeedGenerator.h"
#include <iostream>

EvenSpacedSeedGenerator::EvenSpacedSeedGenerator(int _width, int _height, int _distance) : SeedGenerator(_width, _height), distance(_distance)
{
	mapWidth = ceilf((float)SeedGenerator::width / distance);
	mapHeight = ceilf((float)(float)SeedGenerator::height / distance);
	count = 0;
	map = std::map<int, std::list<Vector2>*>();
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			map[x + y * mapWidth] = new std::list<Vector2>();
			possibleSeeds.push_back(Vector2((float)x, (float)y));
			count++;
			/*for (int i = 0; i < distance; i++) {
				for (int j = 0; j < distance; j++) {
					if ((y + j) >= 550.0f) {
						std::cout << ";";
					}
					if (((x + i) < _width) && ((y + j) < _height)) {
						possibleSeeds.push_back(Vector2((float)x + i, (float)y + j));
						count++;
					}
				}
			}*/
		}
	}
}

EvenSpacedSeedGenerator::~EvenSpacedSeedGenerator()
{

}

Vector2 EvenSpacedSeedGenerator::getNextPoint() {
	if (currentLine.size() > 0) {
		for (Vector2 point : currentLine) {
			int x = (int)point.x() / distance;
			int y = (int)point.y() / distance;
			map[x + y * mapWidth]->push_back(point);
			if (((int)point.x() % distance == 0) && ((int)point.y() % distance == 0)) {
				Vector2 shortPoint = Vector2((float)x, (float)y);
				auto pointer = possibleSeeds.begin();
				bool removed = false;
				while (!removed && pointer != possibleSeeds.end()) {
					if (*pointer == shortPoint) {
						possibleSeeds.erase(pointer);
						count--;
						removed = true;
					}
					else {
						pointer++;
					}
				}
			}
		}
		currentLine.empty();
	}
	bool ok = false;
	while (!ok && possibleSeeds.size() > 0)
	{
		int pos = 0 + (rand() % count);
		Vector2 point = possibleSeeds.at(pos);
		possibleSeeds.erase(possibleSeeds.begin() + pos);
		count--;
		std::cout << count << std::endl;
		if (checkNeighborhood(point)) {
			return point * distance;
		}
	}
	return Vector2((float)nan(""), (float)nan(""));
}

void EvenSpacedSeedGenerator::start() {
}

bool EvenSpacedSeedGenerator::update(Vector2 point) {
	if (checkNeighborhood(point)) {
		currentLine.push_back(point);
		/*int x = (int)point.x() / distance;
		int y = (int)point.y() / distance;
		map[x + y * mapWidth]->push_back(point);
		if (((int)point.x() % distance == 0) && ((int)point.y() % distance == 0)) {
		Vector2 shortPoint = Vector2((float)x, (float)y);
		for (auto pointer = possibleSeeds.begin(); pointer != possibleSeeds.end(); pointer++) {
		if (*pointer == shortPoint) {
		possibleSeeds.erase(pointer);
		count--;
		std::cout << count << std::endl;
		return true;
		}
		}
		}*/
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
			Vector2 distanceVector = other - point;
			float distanceToOther = sqrt(other.x() * other.x() + other.y() * other.y());
			if (distanceToOther > distance) {
				return false;
			}
		}
	}
	return true;
}

bool EvenSpacedSeedGenerator::isFinished() {
	return possibleSeeds.size() <= 0;
}