#pragma once
#include "Window.h"
#include "Widget.h"

Window::Window(VectorField* vectorField) {
	integrator = new EulerIntegration(vectorField, 1000, 1.0f / 10000.0f, 10000);
	integrator->simulate();
	setWindowTitle(tr("Euler Integration"));
	Widget* widget = new Widget(integrator, this);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(widget);
	setLayout(layout);
}

Window::~Window() {

}