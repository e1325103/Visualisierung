#pragma once
#include "Integrator.h"

class RungeKuttaIntegrator : public Integrator {
public:
	RungeKuttaIntegrator(VectorField* _vectorField, int _pointCount, float _delta, int _steps) : Integrator(_vectorField, _pointCount, _delta, _steps) {

	}
	void simulate();
};