#pragma once
#include "EulerIntegration.h"
#include "RungeKuttaIntegration.h"
#include <QWidget>

class Widget : public QWidget
{
public:
	Widget(EulerIntegration* eulerIntegration, QWidget* parent);
	~Widget();
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
private:
	EulerIntegration* eulerIntegration;
};