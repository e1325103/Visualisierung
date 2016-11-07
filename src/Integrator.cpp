#include "Integrator.h"

QPixmap Integrator::paint() {
	QPixmap pix(vectorField->width(), vectorField->height());
	QPainter* painter = new QPainter(&pix);

	painter->setRenderHint(QPainter::Antialiasing);
	//painter->setRenderHint(QPainter::HighQualityAntialiasing);

	painter->fillRect(0, 0, vectorField->width(), vectorField->height(), QBrush(QColor(255, 255, 255)));

	paintBackgroundParameter(painter, 0, Vector3(255, 0, 0), Vector3(0, 0, 255));

	paintLines(painter, 3, Vector3(255, 255, 255));

	delete painter;
	return pix;
}

void Integrator::paintLines(QPainter* painter, int width, Vector3 color) {
	QPen pen;
	pen.setColor(QColor((int)color.x(), (int)color.y(), (int)color.z()));
	pen.setWidth(width);

	for (auto lineIterator = lines.begin(); lineIterator != lines.end(); lineIterator++) {
		std::list<Vector3> points = *lineIterator;
		float i = 0.0f;
		if (points.size() > 1) {
			auto pointIterator = points.begin();
			Vector3 last = *pointIterator++;
			Vector3 current = *pointIterator++;
			while (pointIterator != points.end()) {
				painter->setPen(pen);
				painter->drawLine(last.x(), last.y(), current.x(), current.y());
				last = current;
				current = *pointIterator++;
				i++;
			}
			painter->drawLine(last.x(), last.y(), current.x(), current.y());
		}
		/*else if (points.size() == 1) {
			Vector3 point = *(points.begin()++);
			painter->drawPoint(point.x(), point.y());
		}*/
	}
}

void Integrator::paintBackgroundParameter(QPainter* painter, int parameter, Vector3 color1, Vector3 color2) {
	float maxParameter = std::numeric_limits<float>::min();
	float minParameter = std::numeric_limits<float>::max();

	for (int x = 0; x < vectorField->width(); x++) {
		for (int y = 0; y < vectorField->height(); y++) {
			float parameterValue = vectorField->parameter(x, y)[parameter];
			if (parameterValue > maxParameter) {
				maxParameter = parameterValue;
			}
			if (parameterValue < minParameter) {
				minParameter = parameterValue;
			}
		}
	}

	QPen pen;
	pen.setWidth(1);
	for (int x = 0; x < vectorField->width(); x++) {
		for (int y = 0; y < vectorField->height(); y++) {
			/*float val = interpolateBilinear(x, y, parameter).z();
			val = (val - minParameter) * (1.0f / (maxParameter - minParameter));
			Vector3 mixColor = color1 * val + color2 * (1.0f - val);
			pen.setColor(QColor((int)mixColor.x(), (int)mixColor.y(), (int)mixColor.z()));
			painter->setPen(pen);
			painter->drawPoint(QPoint(x, y));*/

			Vector3 vec = interpolateBilinear(x, y);
			vec.normaliseXY();
			vec = (vec + Vector3(1, 1, 0)) / 2;
			float val = 127.5f * vec.x() + 127.5f * vec.y();
			QColor color = QColor::fromHsv(val, 255, 255);
			pen.setColor(color);
			painter->setPen(pen);
			painter->drawPoint(QPoint(x, y));
		}
	}
}

Vector3 Integrator::interpolateBilinear(float x, float y) {
	return interpolateBilinear(x, y, 0);
}

Vector3 Integrator::interpolateBilinear(float x, float y, int parameter) {
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
	Vector3 v1 = Vector3(vectorField->vector((int)topX, (int)topY), vectorField->parameter((int)topX, (int)topY)[parameter]);
	Vector3 v2 = Vector3(vectorField->vector((int)bottomX, (int)bottomY), vectorField->parameter((int)bottomX, (int)bottomY)[parameter]);
	Vector3 v3 = Vector3(vectorField->vector((int)topX, (int)bottomY), vectorField->parameter((int)topX, (int)bottomY)[parameter]);
	Vector3 v4 = Vector3(vectorField->vector((int)bottomX, (int)topY), vectorField->parameter((int)bottomX, (int)topY)[parameter]);
	Vector3 vTop = v3 * deltaX + v1 * (1.0f - deltaX);
	Vector3 vBottom = v4 * deltaX + v2 * (1.0f - deltaX);
	return  vBottom * deltaY + vTop * (1.0f - deltaY);
}
