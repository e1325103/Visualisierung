#include "Integrator.h"

void Integrator::paint(QPainter* painter, QPaintEvent* event, int elapsed) {
	float maxParameter = 0.0015f;
	float minParameter = 0.0f;
	painter->fillRect(event->rect(), QBrush(QColor(255, 255, 250)));
	QPen pen;
	pen.setWidth(1);
	for (int x = 0; x < 998; x++) {
		for (int y = 0; y < 998; y++) {
			float val = interpolateBilinear(((float)y / 2.0f), ((float)x / 2.0f)).z();
			val = (val - minParameter) * (1.0f / (maxParameter - minParameter));
			//pen.setColor(QColor((int)(255.0f * val), (int)(0.0f), (int)(255 * (1.0f - val))));
			pen.setColor(QColor((int)(0.0f), (int)(255.0f * val), (int)(255 * (1.0f - val))));
			painter->setPen(pen);
			painter->drawPoint(QPoint(x, y));
		}
	}
	pen.setColor(QColor(0, 0, 0));
	pen.setWidth(3);
	for (auto lineIterator = lines.begin(); lineIterator != lines.end(); lineIterator++) {
		std::list<Vector3> points = *lineIterator;
		float i = 0.0f;
		if (points.size() > 1) {
			auto pointIterator = points.begin();
			Vector3 last = *pointIterator++;
			Vector3 current = *pointIterator++;
			while (pointIterator != points.end()) {
				//float val = (current.z() - minParameter) * (1.0f / (maxParameter - minParameter));
				//pen.setColor(QColor((int)(255.0f * val), (int)(0.0f), (int)(255 * (1.0f - val))));
				painter->setPen(pen);
				painter->drawLine(last.x() * 2, last.y() * 2, current.x() * 2, current.y() * 2);
				last = current;
				current = *pointIterator++;
				i++;
			}
			painter->drawLine(last.x() * 2, last.y() * 2, current.x() * 2, current.y() * 2);
		}
		else if (points.size() == 1) {
			Vector3 point = *(points.begin()++);
			painter->drawPoint(point.x(), point.y());
		}
	}
}

Vector3 Integrator::interpolateBilinear(float x, float y) {
	/*Vector2 position = vectorField->vector((int)x, (int)y);
	float parameter = vectorField->parameter((int)x, (int)y)[1];
	if (parameter < minParameter) {
		minParameter = parameter / 10000.0f;
	}
	if (parameter > maxParameter) {
		maxParameter = parameter;
	}
	return Vector3(position.x(), position.y(), parameter);*/

	float topX = ceilf(x);
	float topY = ceilf(y);
	float bottomX = floorf(x);
	float bottomY = floorf(y);
	float deltaX = fabsf(topX - x);
	float deltaY = fabsf(topY - y);
	Vector3 v1 = Vector3(vectorField->vector((int)topX, (int)topY), vectorField->parameter((int)topX, (int)topY)[1]);
	Vector3 v2 = Vector3(vectorField->vector((int)bottomX, (int)bottomY), vectorField->parameter((int)bottomX, (int)bottomY)[1]);
	Vector3 v3 = Vector3(vectorField->vector((int)topX, (int)bottomY), vectorField->parameter((int)topX, (int)bottomY)[1]);
	Vector3 v4 = Vector3(vectorField->vector((int)bottomX, (int)topY), vectorField->parameter((int)bottomX, (int)topY)[1]);
	Vector3 vTop = v3 * deltaX + v1 * (1.0f - deltaX);
	Vector3 vBottom = v4 * deltaX + v2 * (1.0f - deltaX);
	return  vBottom * deltaY + vTop * (1.0f - deltaY);
}