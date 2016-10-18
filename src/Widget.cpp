#include "Widget.h"

Widget::Widget(EulerIntegration* _eulerIntegration, QWidget* _parent) : QWidget(_parent), eulerIntegration(_eulerIntegration) {
	setMinimumSize(_eulerIntegration->vectorField->width() + 40, _eulerIntegration->vectorField->height() + 40);
}

Widget::~Widget() {

}

void Widget::paintEvent(QPaintEvent* event) {
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	eulerIntegration->paint(&painter, event, 0);
	painter.end();
}