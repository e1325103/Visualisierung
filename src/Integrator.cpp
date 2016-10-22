#include "Integrator.h"

void Integrator::paint(QPainter* painter, QPaintEvent* event, int elapsed) {
	painter->fillRect(event->rect(), QBrush(QColor(255, 255, 250)));
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

Vector2 Integrator::interpolateBilinear(float x, float y) {
	return vectorField->vector((int)x, (int)y);
	/*float topX = ceilf(x);
	float topY = ceilf(y);
	float bottomX = floorf(x);
	float bottomY = floorf(y);
	float deltaX = fabsf(topX - x);
	float deltaY = fabsf(topY - y);
	Vector2 v1 = vectorField->vector((int)topY, (int)topX);
	Vector2 v2 = vectorField->vector((int)bottomY, (int)bottomX);
	Vector2 v3 = vectorField->vector((int)topY, (int)bottomX);
	Vector2 v4 = vectorField->vector((int)bottomY, (int)topX);
	Vector2 vTop = v3 * deltaX + v1 * (1.0f - deltaX);
	Vector2 vBottom = v4 * deltaX + v2 * (1.0f - deltaX);
	return vBottom * deltaY + vTop * (1.0f - deltaY);*/
}