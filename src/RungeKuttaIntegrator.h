#pragma once
#include "Integrator.h"

class RungeKuttaIntegrator : public Integrator {
public:
	RungeKuttaIntegrator(VectorField* _vectorField, SeedGenerator* _seedGenerator, float _delta, int _steps) : Integrator(_vectorField, _seedGenerator, _delta, _steps) {

	}
	void simulate();
};