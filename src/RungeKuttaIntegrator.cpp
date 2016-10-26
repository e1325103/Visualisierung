#include "RungeKuttaIntegrator.h"

void RungeKuttaIntegrator::simulate() {
	int currentX = 0;
	int currentY = 0;
	//int count = 0;
	seedGenerator->start();
	while (!seedGenerator->isFinished()) {
		//count++;
		QPoint startPoint = seedGenerator->getNextPoint();
		float x = (float)startPoint.x();
		float y = (float)startPoint.y();

		/*float x = 0 + (rand() % (int)vectorField->width());
		float y = 0 + (rand() % (int)vectorField->height());*/

		std::list<QPoint> points;
		int lastX = -1;
		int lastY = -1;

		bool outside = false;

		for (int j = 0; j < steps && !outside; j++) {

			Vector2 tempV = Integrator::interpolateBilinear(x, y);
			tempV.normalise();

			float tempX = x + tempV.x() * delta / 2.0f;
			float tempY = y + tempV.y() * delta / 2.0f;

			Vector2 v = Integrator::interpolateBilinear(tempX, tempY);
			v.normalise();
			x = x + v.x() * delta;
			y = y + v.y() * delta;

			if (((int)x != lastX) && ((int)y != lastY)) {
				lastX = (int)x;
				lastY = (int)y;
				if (seedGenerator->update(QPoint(lastX, lastY))) {
					points.push_back(QPoint(lastX, lastY));
				}
			}

			outside = x < 0 || y < 0 || ((int)x + 1) >= vectorField->width() || ((int)y + 1) >= vectorField->height();
		}
		lines.push_back(points);
	}

}