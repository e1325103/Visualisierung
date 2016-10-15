#pragma once
#include "VectorField.h"
#include <QPainter>
#include <QPaintEvent>

class EulerIntegration {
public:
	EulerIntegration(VectorField* vectorField);
	~EulerIntegration();

	void paint(QPainter *painter, QPaintEvent *event, int elapsed);
private:
	QBrush background;
};