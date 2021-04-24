#include "myLib.h"
#include <Math.h>
#include <string.h>

float cToF(float degC) {
	return (float)(degC * (9.0F / 5.0F) + 32.0F);
}

float fToC(float degF) {
	return (float)((degF - 32.0F) * (5.0F / 9.0F));
}

Cylinder nextCyl(Cylinder nowCyl) {
	Cylinder newCyl;
	newCyl = (Cylinder)(nowCyl == NUM_CYLS) || (nowCyl < 0) ? CYL_ERROR : nowCyl + 1;
	newCyl = (Cylinder)(((nowCyl < NUM_CYLS) && (nowCyl > 0)) && (newCyl >= NUM_CYLS)) ? 0: newCyl;

	return newCyl;
}

DayOfWeek dayOfWeek(Date date) {
	const int subtractionFactor = 621049;
	int days = numDays(date);
	days -= subtractionFactor;

	return ((DayOfWeek)days % 7);
}

int numDays(Date d1) {
	d1.year = (d1.month <= 2) ? d1.year - 1 : d1.year;
	d1.month = (d1.month <= 2) ? d1.month + 13 : d1.month + 1;
	int numDays = (((1461 * d1.year) / (4)) + ((153 * d1.month) / (5)) + d1.day);

	return numDays;
}

int daysBetween(Date d1, Date d2) {
	int numDays1 = numDays(d1);
	int numDays2 = numDays(d2);

	return (numDays2 - numDays1);
}

float distance(const Point p1, const Point p2) {
	float power1 = powf(p2.x - p1.x, 2);
	float power2 = powf(p2.y - p1.y, 2);

	return (float)(fabs((sqrtf(power1 + power2))));
}

float slope(const Point p1, const Point p2) {
	return (float)((p2.y - p1.y) / (p2.x - p1.x));
}

SlopeIntercept slopeIntercept(const Point p1, const Point p2) {
	SlopeIntercept si;
	si.slope = slope(p1, p2);
	si.yIntercept = (-(si.slope * p1.x) + p1.y);
	si.valid = (p1.x - p2.x) == 0 ? false:true ;

	return si;
}

LinearInterp linearInterp(const Point p1, const Point p2, const float x, const bool limit) {
	LinearInterp lerp;

	float m = slope(p1, p2);
	float tempY = (p1.y + (x - p1.x) * (m));
	lerp.yValue = tempY;

	if (limit) {
		lerp.yValue = (lerp.yValue > p1.y) ? lerp.yValue : p1.y;
		lerp.yValue = (lerp.yValue < p2.y) ? lerp.yValue : p2.y;
		lerp.yValue = ((tempY < p1.y) && (tempY > p2.y)) ? tempY : lerp.yValue;
	}

	if ((p1.x - p2.x) == 0) {
		lerp.yValue = 0;
		lerp.valid = false;
	}
	else {
		lerp.valid = true;
	}
	
	return lerp;
}

Ieee754singleFactors  computeIeee754singleFactors(const Ieee754singlePrecision ieeeNum) {
	Ieee754singleFactors ieee;

	if ((ieeeNum.fields.exponent >= 0x01) && ( ieeeNum.fields.exponent <= 0xFE)) {
		ieee.signFactor = (powf(-1, ieeeNum.fields.sign));
		ieee.exponentFactor = (powf(2, (int)(ieeeNum.fields.exponent - 127)));
		ieee.fractionFactor = (1 + ((float)ieeeNum.fields.fraction / (float)(1 << 23)));
	}
	else {
		ieee.exponentFactor = 0;
		ieee.fractionFactor = 0;
		ieee.signFactor = 0;
	}

	return ieee;
}

unsigned stringLength(const char* const pS) {
	unsigned i;
	for (i = 0; pS[i] != '\0'; i++) {}
	return (i);
}

unsigned stringCopy(const char* const from, char* to) {
	unsigned i;
	for (i = 0; from[i] != '\0'; i++) {
		to[i] = from[i];
	}
	to[i] = '\0';

	return(i);
}

unsigned stringReverse(const char* const from, char* to) {
	unsigned len = stringLength(from);

	for (unsigned i = 0; i < len; i++) {
		to[i] = from[(len - 1) - i];
	}
	to[len] = '\0';
	return(len);
}