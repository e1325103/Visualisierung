#pragma once
#include "Window.h"
#include "Widget.h"

Window::Window(VectorField* vectorField) {
	eulerIntegration = new EulerIntegration(vectorField, 10000, 1.0f/100.0f, 400);
	eulerIntegration->simulate();
	setWindowTitle(tr("Euler Integration"));
	Widget* widget = new Widget(eulerIntegration, this);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(widget);
	setLayout(layout);
}

Window::~Window() {

}