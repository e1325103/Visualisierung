
#include "LIC.h"

void LIC::simulate()
{
	float** noise = new float*[vectorField->height()];

	for (int i = 0; i < vectorField->height(); i++) {
		noise[i] = new float[vectorField->width()];
	}

	for (int i = 0; i < vectorField->height(); i++) {
		for (int j = 0; j < vectorField->width(); j++) {
			noise[i][j] = ((float)rand() / (RAND_MAX));
		}
	}
				

	bool finished = false;

	for (int j = 0; j < vectorField->height(); j++) {
		for (int i = 0; i < vectorField->width(); i++)
		{

			float noiseSum[2];
			float sumWeight[2];

			noiseSum[0] = 0.0f;
			noiseSum[1] = 0.0f;
			sumWeight[0] = 0.0f;
			sumWeight[1] = 0.0f;


			for (int direction = 0; direction < 2; direction++) // 0 vorwaerts, 1 rueckwaerts
			{
				int stepCounter = 0;

				float currentLength = 0.0f;

				float borderX = i + 0.5f;
				float borderY = j + 0.5f;


				finished = false;

				while (currentLength < 10.0f && stepCounter < 30 && !finished)
				{
					Vector2 vector = vectorField->vector(borderX, borderY);
					vector.normalise();



					if (vector.x() == 0.0f && vector.y() == 0.0f)
					{
						if (stepCounter == 0) {
							noiseSum[direction] = 0.0f;
							sumWeight[direction] = 1.0f;
						}

						finished = true;
					}
					else  {


						if (direction == 1) {
							vector = vector * -1.0f;
						}


						// Segmentlaenge berechnen**********************************

						float stepLength = 100000.0f;

						if (vector.x() < 0.0f) {
							stepLength = (int(borderX) - borderX) / vector.x();
						}
						else if (vector.x() > 0.0f) {
							stepLength = (int(int(borderX) + 1.5f) - borderX);
						}


						if (vector.y() < 0.0f) {
							float tempStepLength = (int(borderY) - borderY) / vector.y();

							if (tempStepLength < stepLength) {
								stepLength = tempStepLength;
							}

						}
						else if (vector.y() > 0.0f) {
							float tempStepLength = int(int(borderY) + 1.5f) - borderY;

							if (tempStepLength < stepLength) {
								stepLength = tempStepLength;
							}
						}

						//***********************************************************

						float previousLength = currentLength;
						currentLength += stepLength;
						stepLength += 0.0004f;



						if (currentLength > 10.0f) {
							currentLength = 10.0f;
							stepLength = 10.0f - previousLength;
						}


						float nextBorderX = borderX + vector.x() * stepLength;
						float nextBorderY = borderY + vector.y() * stepLength;
							 

						float noiseCoordX = (borderX + nextBorderX) * 0.5f;
						float noiseCoordY = (borderY + nextBorderY) * 0.5f;


						if (!isInside(noiseCoordX, noiseCoordY)) {
							finished = true;
						}
						else {

							float pixelValue = noise[int(noiseCoordY)][int(noiseCoordX)];

							
							float currentWeight = (currentLength - previousLength);
							sumWeight[direction] += currentWeight;
							noiseSum[direction] += pixelValue * currentWeight;
							

							stepCounter++;
							borderX = nextBorderX;
							borderY = nextBorderY;


							if (!isInside(borderX, borderY)) {
								finished = true;
							}
						}
					}
				}
			}

			float pixelValue = (noiseSum[0] + noiseSum[1]) / (sumWeight[0] + sumWeight[1]);
			
			vectorField->setParameter(i, j, 2, pixelValue);
		}
	}
}

bool LIC::isInside(int x, int y) {
	if (x >= 0 && y >= 0 && x < vectorField->width() && y < vectorField->height()) {
		return true;
	}

	return false;
}