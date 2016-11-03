#pragma once
#include "EulerIntegrator.h"
#include "RungeKuttaIntegrator.h"
#include <QWidget>

class Widget : public QWidget
{
public:
	Widget(Integrator* integrator, QWidget* parent);
	~Widget();
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
private:
	Integrator* integrator;
	QPixmap currentPix;
	bool redraw = true;
};