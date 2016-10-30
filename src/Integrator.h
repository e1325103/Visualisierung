#pragma once
#include "SeedGenerator.h"
#include "VectorField.h"
#include "Vector.h"

#include <cfloat>
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
	Vector3 interpolateBilinear(float x, float y);

	VectorField* vectorField;
protected:
	SeedGenerator* seedGenerator;
	float delta;
	int steps;
	std::list<std::list<Vector3>> lines;

	float maxParameter = 0.000001f;
	float minParameter = 0.0f;
};