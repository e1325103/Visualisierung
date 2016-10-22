#pragma once
#include "Integrator.h"

class EulerIntegrator : public Integrator {
public:
	EulerIntegrator(VectorField* _vectorField, int _pointCount, float _delta, int _steps) : Integrator(_vectorField, _pointCount, _delta, _steps) {

	}
	void simulate();
};