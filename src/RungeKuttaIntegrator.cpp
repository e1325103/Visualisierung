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

		std::list<Vector3> points;
		int lastX = -1;
		int lastY = -1;

		bool outside = false;

		for (int j = 0; j < steps && !outside; j++) {

			Vector3 tempV = Integrator::interpolateBilinear(y, x);
			tempV.normaliseXY();

			float tempX = x + tempV.x() * delta / 2.0f;
			float tempY = y + tempV.y() * delta / 2.0f;

			outside = tempX < 0 || tempY < 0 || ((int)tempX + 1) >= vectorField->width() || ((int)tempY + 1) >= vectorField->height();

			if (!outside) {
				Vector3 v = Integrator::interpolateBilinear(tempY, tempX);
				v.normaliseXY();
				x = x + v.x() * delta;
				y = y + v.y() * delta;

				outside = x < 0 || y < 0 || ((int)x + 1) >= vectorField->width() || ((int)y + 1) >= vectorField->height();

				if (((int)x != lastX) && ((int)y != lastY)) {
					lastX = (int)x;
					lastY = (int)y;
					if (seedGenerator->update(QPoint(lastX, lastY))) {
						points.push_back(Vector3(x, y, v.z()));
					}
					else {
						outside = true;
					}
				}
			}
		}
		if (points.size() > 0) {
			lines.push_back(points);
		}
	}

}