
#include "LIC.h"

void	LIC::simulate()
{
	float** noise = new float*[vectorField->height()];

	for (int i = 0; i < vectorField->height(); i++) {
		noise[i] = new float[vectorField->width()];
	}

	for (int i = 0; i < vectorField->height(); i++) {
		for (int j = 0; j < vectorField->width(); j++) {
			noise[i][j] = ((float)rand() / (RAND_MAX)) + 1;
		}
	}

	int		vec_id;						///ID in the VECtor buffer (for the input flow field)
	int		advDir;						///ADVection DIRection (0: positive;  1: negative)
	int		advcts;						///number of ADVeCTion stepS per direction (a step counter)
	int		ADVCTS = int(10 * 3);	///MAXIMUM number of advection steps per direction to break dead loops	

	float	vctr_x;						///x-component  of the VeCToR at the forefront point
	float	vctr_y;						///y-component  of the VeCToR at the forefront point
	float	clp0_x;						///x-coordinate of CLiP point 0 (current)
	float	clp0_y;						///y-coordinate of CLiP point 0	(current)
	float	clp1_x;						///x-coordinate of CLiP point 1 (next   )
	float	clp1_y;						///y-coordinate of CLiP point 1 (next   )
	float	samp_x;						///x-coordinate of the SAMPle in the current pixel
	float	samp_y;						///y-coordinate of the SAMPle in the current pixel
	float	tmpLen;						///TeMPorary LENgth of a trial clipped-segment
	float	segLen;						///SEGment   LENgth
	float	curLen;						///CURrent   LENgth of the streamline
	float	prvLen;						///PReVious  LENgth of the streamline		
	float	W_ACUM;						///ACcuMulated Weight from the seed to the current streamline forefront
	float	texVal;						///TEXture VALue
	float	smpWgt;						///WeiGhT of the current SaMPle
	float	t_acum[2];					///two ACcUMulated composite Textures for the two directions, perspectively
	float	w_acum[2];					///two ACcUMulated Weighting values   for the two directions, perspectively
	float*	wgtLUT = NULL;				///WeiGhT Look Up Table pointing to the target filter LUT
	float	len2ID = (2048 - 1) / 10.0f;	///map a curve LENgth TO an ID in the LUT

	float*			p_LUT0 = (float*)malloc(sizeof(float) * 2048);
	float*			p_LUT1 = (float*)malloc(sizeof(float) * 2048);
	for (int i = 0; i < 2048; i++)  p_LUT0[i] = p_LUT1[i] = i;

	///for each pixel in the 2D output LIC image///
	for (int j = 0; j < vectorField->height(); j++)
		for (int i = 0; i < vectorField->width(); i++)
		{
		///init the composite texture accumulators and the weight accumulators///
		t_acum[0] = t_acum[1] = w_acum[0] = w_acum[1] = 0.0f;

		///for either advection direction///
		for (advDir = 0; advDir < 2; advDir++)
		{
			///init the step counter, curve-length measurer, and streamline seed///
			advcts = 0;
			curLen = 0.0f;
			clp0_x = i + 0.5f;
			clp0_y = j + 0.5f;

			///access the target filter LUT///
			wgtLUT = (advDir == 0) ? p_LUT0 : p_LUT1;

			///until the streamline is advected long enough or a tightly  spiralling center / focus is encountered///
			while (curLen < 10.0f && advcts < ADVCTS)
			{
				///access the vector at the sample///
				//vec_id = (int(clp0_y) * vectorField->width() + int(clp0_x)) << 1;
				Vector2 vctr = vectorField->vector(clp0_x, clp0_y);
				vctr.normalise();
				vctr_x = vctr.x();
				vctr_y = vctr.y();

				///in case of a critical point///
				if (vctr_x == 0.0f && vctr_y == 0.0f)
				{
					t_acum[advDir] = (advcts == 0) ? 0.0f : t_acum[advDir];		   ///this line is indeed unnecessary
					w_acum[advDir] = (advcts == 0) ? 1.0f : w_acum[advDir];
					break;
				}

				///negate the vector for the backward-advection case///
				vctr_x = (advDir == 0) ? vctr_x : -vctr_x;
				vctr_y = (advDir == 0) ? vctr_y : -vctr_y;

				///clip the segment against the pixel boundaries --- find the shorter from the two clipped segments///
				///replace  all  if-statements  whenever  possible  as  they  might  affect the computational speed///
				segLen = 100000.0f;
				segLen = (vctr_x < -0.050000f) ? (int(clp0_x) - clp0_x) / vctr_x : segLen;
				segLen = (vctr_x > 0.050000f) ? (int(int(clp0_x) + 1.5f) - clp0_x) / vctr_x : segLen;
				segLen = (vctr_y < -0.050000f) ?
					(((tmpLen = (int(clp0_y) - clp0_y) / vctr_y) < segLen) ? tmpLen : segLen)
					: segLen;
				segLen = (vctr_y > 0.050000f) ?
					(((tmpLen = (int(int(clp0_y) + 1.5f) - clp0_y) / vctr_y) < segLen) ? tmpLen : segLen)
					: segLen;

				///update the curve-length measurers///
				prvLen = curLen;
				curLen += segLen;
				segLen += 0.0004f;

				///check if the filter has reached either end///
				segLen = (curLen > 10.0f) ? ((curLen = 10.0f) - prvLen) : segLen;

				///obtain the next clip point///
				clp1_x = clp0_x + vctr_x * segLen;
				clp1_y = clp0_y + vctr_y * segLen;

				///obtain the middle point of the segment as the texture-contributing sample///
				samp_x = (clp0_x + clp1_x) * 0.5f;
				samp_y = (clp0_y + clp1_y) * 0.5f;
				if (samp_x < 0.0f || samp_x >= vectorField->width() || samp_y < 0.0f || samp_y >= vectorField->height())  break;
				///obtain the texture value of the sample///
				texVal = noise[int(samp_y)][int(samp_x)];

				///update the accumulated weight and the accumulated composite texture (texture x weight)///
				W_ACUM = wgtLUT[int(curLen * len2ID)];
				smpWgt = W_ACUM - w_acum[advDir];
				w_acum[advDir] = W_ACUM;
				t_acum[advDir] += texVal * smpWgt;

				///update the step counter and the "current" clip point///
				advcts++;
				clp0_x = clp1_x;
				clp0_y = clp1_y;

				///check if the streamline has gone beyond the flow field///
				if (clp0_x < 0.0f || clp0_x >= vectorField->width() || clp0_y < 0.0f || clp0_y >= vectorField->height())  break;
			}
		}

		///normalize the accumulated composite texture///
		texVal = (t_acum[0] + t_acum[1]) / (w_acum[0] + w_acum[1]);

		///clamp the texture value against the displayable intensity range [0, 255]
		texVal = (texVal < 0.0f) ? 0.0f : texVal;
		texVal = (texVal > 255.0f) ? 255.0f : texVal;
		vectorField->setParameter(i, j, 2, texVal);
		}

	//void LIC::simulate() {
	//	
	//	float** noise = new float*[vectorField->height()];
	//
	//	for (int i = 0; i < vectorField->height(); i++) {
	//		noise[i] = new float[vectorField->width()];
	//	}
	//
	//	for (int i = 0; i < vectorField->height(); i++) {
	//		for (int j = 0; j < vectorField->width(); j++) {
	//			noise[i][j] = ((float)rand() / (RAND_MAX)) + 1;
	//		}
	//	}
	//
	//	int x1, y1, x2, y2;
	//
	//	float pixelValue = 0;
	//
	//	
	//
	//	float weights[] = { 0.08233f, 0.081929f, 0.08071f, 0.078719f, 0.076014f, 0.072672f, 0.068786f };
	//
	//	
	//	//float weights[] = { 0.056461f, 0.05618f, 0.055344f, 0.053979f, 0.052124f, 0.049832f, 0.047168f, 0.044202f, 0.04101f, 0.037671f, 0.03426f };
	//
	//	for (int x = 0; x < vectorField->width(); x++) {
	//		for (int y = 0; y < vectorField->height(); y++) {
	//
	//			x1 = x;
	//			y1 = y;
	//
	//			x2 = x;
	//			y2 = y;
	//
	//			pixelValue = 0;
	//
	//			//vectorField->setParameter(x, y, 2, noise[y][x]);
	//			
	//			pixelValue += noise[y][x] * weights[0];
	//
	//			for (int k = 1; k <= kernelSize; k++) {
	//
	//				// forward ***************************************************
	//				Vector2 vector = vectorField->vector(x1, y1);
	//				vector.normalise();
	//				vector = vector * 0.0006;
	//				
	//
	//				if (isInside(x1 + vector.x() * 1, y1 + vector.y() * 1)) {
	//					x1 = x1 + vector.x() * 1;
	//					y1 = y1 + vector.y() * 1;
	//
	//
	//				}
	//
	//				pixelValue += noise[y1][x1] * weights[k];
	//				// ************************************************************
	//
	//
	//
	//
	//				// backward **************************************************
	//				vector = vectorField->vector(x2, y2);
	//				vector.normalise();
	//				vector = vector * 0.0006;
	//
	//				if (isInside(x2 - vector.x() * 1, y2 - vector.y() * 1)) {
	//					x2 = x2 - vector.x() * 1;
	//					y2 = y2 - vector.y() * 1;
	//				}
	//
	//				pixelValue += noise[y2][x2] * weights[k];
	//				// ************************************************************
	//
	//				
	//			}		
	//
	//			
	//			vectorField->setParameter(x, y, 2, pixelValue);
	//		}
	//	}
	//		 
	//


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