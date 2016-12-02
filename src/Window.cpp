#pragma once
#include "Window.h"
#include "Widget.h"
#include "RandomSeedGenerator.h"
#include "EvenSpacedSeedGenerator.h"

Window::Window(VectorField* vectorField) {
	integrator = new RungeKuttaIntegrator(vectorField, new EvenSpacedSeedGenerator(vectorField->width(), vectorField->height(), 25, 2.0f, 0.5f), 1.0f / 1.0f, 1600, 1, false);
	integrator->simulate();
	setWindowTitle(tr("Euler Integration"));
	Widget* widget = new Widget(integrator, this);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(widget);
	setLayout(layout);
}

Window::~Window() {

}