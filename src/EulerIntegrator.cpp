#include "EulerIntegrator.h"

void EulerIntegrator::simulate() {
	int currentX = 0;
	int currentY = 0;
	seedGenerator->start();
	while (!seedGenerator->isFinished()) {

		QPoint startPoint = seedGenerator->getNextPoint();
		float x = (float)startPoint.x();
		float y = (float)startPoint.y();

		std::list<Vector3> points;
		int lastX = -1;
		int lastY = -1;
		bool outside = false;
		for (int j = 0; j < steps && !outside; j++) {
			Vector2 v = vectorField->vector((int)x, (int)y); //gg
			//v.normalise();
			x = x + v.x() * delta;
			y = y + v.y() * delta;
			if (((int)x != lastX) && ((int)y != lastY)) {
				lastX = (int)x;
				lastY = (int)y;
				points.push_back(Vector3(lastX, lastY, 0));
			}
			outside = x < 0 || y < 0 || ((int)x + 1) >= vectorField->width() || ((int)y + 1) >= vectorField->height();
		}
		lines.push_back(points);
	}
}