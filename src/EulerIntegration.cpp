#include "EulerIntegration.h"

EulerIntegration::EulerIntegration(VectorField* _vectorField, int _pointCount, float _delta, int _steps) {
	background = QBrush(QColor(255, 255, 250));
	vectorField = _vectorField;
	pointCount = _pointCount;
	delta = _delta;
	steps = _steps;
}

EulerIntegration::~EulerIntegration() {

}

void EulerIntegration::paint(QPainter* painter, QPaintEvent* event, int elapsed) {
	painter->fillRect(event->rect(), background);
	QPen pen;
	pen.setColor(QColor(0, 0, 0));
	for (auto lineIterator = lines.begin(); lineIterator != lines.end(); lineIterator++) {
		std::list<QPoint> points = *lineIterator;
		float i = 0.0f;
		if (points.size() > 1) {
			auto pointIterator = points.begin();
			QPoint last = *pointIterator++;
			QPoint current = *pointIterator++;
			while (pointIterator != points.end()) {
				float val = i / points.size();
				pen.setColor(QColor((int)(255.0f * val), (int)(255 * val), (int)(255 * val)));
				pen.setWidth(3);
				painter->setPen(pen);
				painter->drawLine(last, current);
				last = current;
				current = *pointIterator++;
				i++;
			}
			painter->drawLine(last, current);
		}
		else {
			painter->drawPoint(*(points.begin()++));
		}
	}
}

void EulerIntegration::simulate() {
	int currentX = 0;
	int currentY = 0;
	for (int i = 0; i < pointCount; i++) {
		float x = 0 + (rand() % (int)(vectorField->width()));
		float y = 0 + (rand() % (int)(vectorField->height()));
		/*float x = (float)currentX;
		float y = (float)currentY;

		currentX += 10;
		if (currentX >= vectorField->width()) {
			currentX = 0;
			currentY += 10;
			currentY %= vectorField->height();
		}*/

		std::list<QPoint> points;
		int lastX = -1;
		int lastY = -1;
		bool outside = false;
		for (int j = 0; j < steps && !outside; j++) {
			Vector2 v = vectorField->vector((int)x, (int)y);
			x = x - v.x() * delta;
			y = y - v.y() * delta;
			if (((int)x != lastX) && ((int)y != lastY)) {
				lastX = (int)x;
				lastY = (int)y;
				points.push_back(QPoint(lastX, lastY));
			}
			outside = x < 0 || y < 0 || ((int)x + 1) >= vectorField->width() || ((int)y + 1) >= vectorField->height();
		}
		lines.push_back(points);
	}
}