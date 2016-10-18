#pragma once
#include "VectorField.h"
#include <QPainter>
#include <QPaintEvent>

class RungeKuttaIntegration {
public:
	RungeKuttaIntegration(VectorField* _vectorField, int _pointCount, float _delta, int _steps);
	~RungeKuttaIntegration();

	void paint(QPainter *painter, QPaintEvent *event, int elapsed);
	void simulate();

	VectorField* vectorField;
private:
	QBrush background;
	int pointCount;
	float delta;
	int steps;
	std::list<std::list<QPoint>> lines;
};