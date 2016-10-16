#pragma once
#include "Window.h"
#include "Widget.h"

Window::Window(VectorField* vectorField) {
	eulerIntegration = new EulerIntegration(vectorField);
	setWindowTitle(tr("Euler Integration"));
	Widget* widget = new Widget(eulerIntegration, this);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(widget);
	setLayout(layout);
}

Window::~Window() {

}