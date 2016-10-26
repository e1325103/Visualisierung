#pragma once
#include "SeedGenerator.h"
#include "VectorField.h"
#include "Vector.h"

#include <QPainter>
#include <QPaintEvent>

class Integrator
{
public:
	explicit
		Integrator(VectorField* _vectorField, SeedGenerator* _seedGenerator, float _delta, int _steps) :
		vectorField(_vectorField), seedGenerator(_seedGenerator), delta(_delta), steps(_steps) { }
	~Integrator();
	virtual void simulate() = 0;
	void paint(QPainter* painter, QPaintEvent* event, int elapsed);
	Vector2 interpolateBilinear(float x, float y);

	VectorField* vectorField;
protected:
	SeedGenerator* seedGenerator;
	float delta;
	int steps;
	std::list<std::list<QPoint>> lines;
};