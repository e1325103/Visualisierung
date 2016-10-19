#pragma once
#include "EulerIntegration.h"
#include "RungeKuttaIntegration.h"
#include <QGridLayout>

class Window : public QWidget
{
public:
	Window(VectorField* vectorField);
	~Window();

private:
	EulerIntegration* integrator;
};