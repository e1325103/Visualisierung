#pragma once
#include <QPainter>

#include <list>

class SeedGenerator
{
public:
	SeedGenerator(int _width, int _height);
	~SeedGenerator();

	virtual QPoint getNextPoint() = 0;
	virtual void start() = 0;
	virtual bool update(QPoint point) = 0;
	virtual bool isFinished() = 0;
protected:
	int width;
	int height;
};