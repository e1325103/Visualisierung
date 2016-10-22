#include "Widget.h"

Widget::Widget(Integrator* _integrator, QWidget* _parent) : QWidget(_parent), integrator(_integrator) {
	setMinimumSize(_integrator->vectorField->width() + 40, _integrator->vectorField->height() + 40);
}

Widget::~Widget() {

}

void Widget::paintEvent(QPaintEvent* event) {
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	integrator->paint(&painter, event, 0);
	painter.end();
}