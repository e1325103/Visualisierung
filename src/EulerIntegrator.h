#pragma once
#include "Integrator.h"

class EulerIntegrator : public Integrator {
public:
	EulerIntegrator(VectorField* _vectorField, SeedGenerator* _seedGenerator, float _delta, int _steps) : Integrator(_vectorField, _seedGenerator, _delta, _steps) {

	}
	void simulate();
};