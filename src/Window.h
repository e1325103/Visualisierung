#pragma once
#include "EulerIntegrator.h"
#include "RungeKuttaIntegrator.h"
#include <QGridLayout>

class Window : public QWidget
{
public:
	Window(VectorField* vectorField);
	~Window();

private:
	Integrator* integrator;
};