#pragma once
#include "Window.h"
#include "Widget.h"
#include "RandomSeedGenerator.h"
#include "EvenSpacedSeedGenerator.h"

Window::Window(VectorField* vectorField) {
	integrator = new RungeKuttaIntegrator(vectorField, new RandomSeedGenerator(vectorField->width(), vectorField->height(), 400), 1.0f / 10.0f, 1000);
	integrator->simulate();
	setWindowTitle(tr("Euler Integration"));
	Widget* widget = new Widget(integrator, this);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(widget);
	setLayout(layout);
}

Window::~Window() {

}