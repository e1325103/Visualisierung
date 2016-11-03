#include "Widget.h"

Widget::Widget(Integrator* _integrator, QWidget* _parent) : QWidget(_parent), integrator(_integrator) {
	setMinimumSize(_integrator->vectorField->width() * 2 + 40, _integrator->vectorField->height() * 2 + 40);
}

Widget::~Widget() {

}

void Widget::paintEvent(QPaintEvent* event) {
	if (redraw) {
		currentPix = integrator->paint();
		redraw = false;
	}
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPixmap(0, 0, 1000, 1000, currentPix, 0, 0, 500, 500);
	painter.end();
}