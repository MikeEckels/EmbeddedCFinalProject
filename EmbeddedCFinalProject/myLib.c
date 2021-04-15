#include "myLib.h"

float cToF(float degC) {
	return (float)(degC * (9.0F / 5.0F) + 32.0F);
}

float fToC(float degF) {
	return (float)((degF - 32.0F) * (5.0F / 9.0F));
}

Cylinder nextCyl(Cylinder nowCyl) {
	Cylinder newCyl;

	switch (nowCyl) {
		case L1:
			newCyl = R1;
			break;
		case L2:
			newCyl = R2;
			break;
		case R1:
			newCyl = L2;
			break;
		case R2:
			newCyl = L1;
			break;
		default:
			newCyl = CYL_ERROR;
	}
	return newCyl;
}

DayOfWeek dayOfWeek(Date date) {
	const int subtractionFactor = 621049;
	Date dateZero = { 0 };
	DayOfWeek dow;

	int days = daysBetween(dateZero, date);
	days -= subtractionFactor;
	days %= 7;

	switch (days) {
	case 0:
		dow = SUNDAY;
		break;
	case 1:
		dow = MONDAY;
		break;
	case 2:
		dow = TUESDAY;
		break;
	case 3:
		dow = WEDNESDAY;
		break;
	case 4:
		dow = THURSDAY;
		break;
	case 5:
		dow = FRIDAY;
		break;
	case 6:
		dow = SATURDAY;
		break;
	default:
		dow = -1;
	}

	return dow;
}

int daysBetween(Date d1, Date d2) {
	
	d1.year = (d1.month <= 2) ? d1.year - 1 : d1.year;
	d2.year = (d2.month <= 2) ? d2.year - 1 : d2.year;

	d1.month = (d1.month <= 2) ? d1.month + 13 : d1.month + 1;
	d2.month = (d2.month <= 2) ? d2.month + 13 : d2.month + 1;

	int numDays1 = (((1461 * d1.year)/(4)) + ((153 * d1.month)/(5)) + d1.day);
	int numDays2 = (((1461 * d2.year) / (4)) + ((153 * d2.month) / (5)) + d2.day);

	return (numDays2 - numDays1);
}

float distance(const Point p1, const Point p2) {

}

SlopeIntercept slopeIntercept(const Point p1, const Point p2) {

}

LinearInterp linearInterp(const Point p1, const Point p2, const float x, const bool limit) {

}

Ieee754singleFactors  computeIeee754singleFactors(const Ieee754singlePrecision ieeeNum) {

}