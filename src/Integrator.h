#pragma once
#include "VectorField.h"
#include "Vector.h"

#include <QPainter>
#include <QPaintEvent>

class Integrator
{
public:
	explicit
		Integrator(VectorField* _vectorField, int _pointCount, float _delta, int _steps) :
		vectorField(_vectorField), pointCount(_pointCount), delta(_delta), steps(_steps) { }
	~Integrator();
	virtual void simulate() = 0;
	void paint(QPainter* painter, QPaintEvent* event, int elapsed);
	Vector2 interpolateBilinear(float x, float y);

	VectorField* vectorField;
protected:
	int pointCount;
	float delta;
	int steps;
	std::list<std::list<QPoint>> lines;
};