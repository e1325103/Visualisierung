#include "EulerIntegrator.h"

void EulerIntegrator::simulate() {
	int currentX = 0;
	int currentY = 0;
	for (int i = 0; i < pointCount; i++) {
		float x = 0 + (rand() % (int)(vectorField->width()));
		float y = 0 + (rand() % (int)(vectorField->height()));

		std::list<QPoint> points;
		int lastX = -1;
		int lastY = -1;
		bool outside = false;
		for (int j = 0; j < steps && !outside; j++) {
			Vector2 v = vectorField->vector((int)y, (int)x); //gg
			x = x + v.x() * delta;
			y = y + v.y() * delta;
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