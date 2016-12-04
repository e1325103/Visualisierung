#pragma once
#include "Integrator.h"

class LIC : public Integrator {
public:
	LIC(VectorField* _vectorField, SeedGenerator* _seedGenerator, float _delta, int _steps, int _colour, bool _arrows, int _kernelSize) : Integrator(_vectorField, _seedGenerator, _delta, _steps, _colour, _arrows), kernelSize(_kernelSize){

	}
	void simulate();

private:

	int kernelSize;

	bool isInside(int x, int y);
};

/*#pragma once
#include "VectorField.h"
#include "Vector.h"

#include <math.h>
#include <cfloat>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>


class LIC
{
public:
	explicit
		LIC(VectorField* _vectorField, float _delta, int _kernelSize, int _width, int _height) :
		vectorField(_vectorField), delta(_delta), kernelSize(_kernelSize), width(_width), height(_height) { 
		
		}
	~LIC();

	void simulate();

	QPixmap paint();
	Vector3 interpolateBilinear(float x, float y);
	Vector3 interpolateBilinear(float x, float y, int parameter);

	

private:

	VectorField* vectorField;
	float delta;
	int kernelSize;	

	const int width;
	const int height;


	int* noise;


	const int getWidth() const;
	const int getHeight() const;

	std::list<std::list<Vector3>> lines;	
};*/