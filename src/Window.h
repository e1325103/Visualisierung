#pragma once
#include "EulerIntegration.h"
#include <QGridLayout>

class Window : public QWidget
{
public:
	Window(VectorField* vectorField);
	~Window();

private:
	EulerIntegration* eulerIntegration;
};