
#include "LIC.h"

void LIC::simulate() {
	
	float** noise = new float*[vectorField->height()];

	for (int i = 0; i < vectorField->height(); i++) {
		noise[i] = new float[vectorField->width()];
	}

	for (int i = 0; i < vectorField->height(); i++) {
		for (int j = 0; j < vectorField->width(); j++) {
			noise[i][j] = ((float)rand() / (RAND_MAX)) + 1;
		}
	}

	int x1, y1, x2, y2;

	float pixelValue = 0;

	

	float weights[] = { 0.08233f, 0.081929f, 0.08071f, 0.078719f, 0.076014f, 0.072672f, 0.068786f };

	
	//float weights[] = { 0.056461f, 0.05618f, 0.055344f, 0.053979f, 0.052124f, 0.049832f, 0.047168f, 0.044202f, 0.04101f, 0.037671f, 0.03426f };

	for (int x = 0; x < vectorField->width(); x++) {
		for (int y = 0; y < vectorField->height(); y++) {

			x1 = x;
			y1 = y;

			x2 = x;
			y2 = y;

			pixelValue = 0;

			//vectorField->setParameter(x, y, 2, noise[y][x]);
			
			pixelValue += noise[y][x] * weights[0];

			for (int k = 1; k <= kernelSize; k++) {

				// forward ***************************************************
				Vector2 vector = vectorField->vector(x1, y1);
				vector.normalise();
				vector = vector * 6;
				

				if (isInside(x1 + vector.x() * 1, y1 + vector.y() * 1)) {
					x1 = x1 + vector.x() * 1;
					y1 = y1 + vector.y() * 1;


				}

				pixelValue += noise[y1][x1] * weights[k];
				// ************************************************************




				// backward **************************************************
				vector = vectorField->vector(x2, y2);
				vector.normalise();
				vector = vector * 6;

				if (isInside(x2 - vector.x() * 1, y2 - vector.y() * 1)) {
					x2 = x2 - vector.x() * 1;
					y2 = y2 - vector.y() * 1;
				}

				pixelValue += noise[y2][x2] * weights[k];
				// ************************************************************

				
			}		

			
			vectorField->setParameter(x, y, 2, pixelValue);
		}
	}
		 

	

	/*int currentX = 0;
	int currentY = 0;
	seedGenerator->start();
	while (!seedGenerator->isFinished()) {

		Vector2 startPoint = seedGenerator->getNextPoint();
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
	}*/
}

bool LIC::isInside(int x, int y) {
	if (x >= 0 && y >= 0 && x < vectorField->width() && y < vectorField->height()) {
		return true;
	}

	return false;
}


/*#include "LIC.h"


void LIC::simulate() {
		
	///int* noise[getHeight()][getWidth()];

	std::vector<int> noise[vectorField->width()][4];

	std::matri

	for (int x = 0; x < vectorField->width(); x++) {
		for (int y = 0; y < vectorField->height(); y++) {



		}
	}

	/*int currentX = 0;
	int currentY = 0;
	seedGenerator->start();
	while (!seedGenerator->isFinished()) {

		Vector2 startPoint = seedGenerator->getNextPoint();
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
		lines.push_back(points);*/
	//}

/*}

const int LIC::getWidth() const
{
	return width;
}

const int LIC::getHeight() const
{
	return height;
}*/