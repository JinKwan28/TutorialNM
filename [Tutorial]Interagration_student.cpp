/*-------------------------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author           : [YOUR NAME]
Created          : 17-05-2021
Modified         : 17-05-2021
Language/ver     : C++ in MSVS2019

Description      : [Tutorial]Integration_student.cpp
-------------------------------------------------------------------------------*/

#include "myNM.h"



// You need to create myFunc() in this main source file

double myFunc_inte(const double _x) {
	return sqrt(1 - pow(_x, 2));
}

int main(int argc, char* argv[])
{
	// PART 1. Integration from Datasets
	CROSSLINE;
	printf("\n       PART 1. Integration from Datasets        \n ");
	CROSSLINE;

	double x[] = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60 };
	double y[] = { 0, 3, 8, 20, 33, 42, 40, 48, 60, 12, 8, 4, 3 };
	int M = sizeof(x) / sizeof(x[0]);

	double I_rect = IntegrateRect(x, y, M);
	double I_trapz = trapz(x,y,M);

	printf("I_rect=%f\n\n", I_rect);
	printf("I_trapz = %f\n\n", I_trapz);

	

	// PART 2. Integration from a Function
	CROSSLINE;
	printf("\n        PART 2. Integration from a Function       \n");
	CROSSLINE;

	double a = -1;
	double b = 1;
	double N = 10000;
	double I_simpson13 = Simpson13(myFunc_inte, a, b, N);
	double I_simpson38 = Simpson38(myFunc_inte, a, b, N);
	printf("I_simpson13  = %f\n\n", I_simpson13);
	printf("I_simpson38 = %f\n\n", I_simpson38);
	printf("Real_Answer(pi/2) = %f\n", PI / 2);
	system("pause");
	return 0;
}







