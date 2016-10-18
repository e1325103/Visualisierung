#pragma once
#include "VectorField.h"
#include <QPainter>
#include <QPaintEvent>

class EulerIntegration {
public:
	EulerIntegration(VectorField* _vectorField, int _pointCount, float _delta, int _steps);
	~EulerIntegration();

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