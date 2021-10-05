/*----------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author           : [YOUR NAME]
Created          : 26-03-2018
Modified         : 18-03-2021
Language/ver     : C++ in MSVS2019

Description      : myNM.cpp
----------------------------------------------------------------*/

#include "myNM.h"

double myFunc(const double _x) {

	return  _x * _x * _x;;

}
void printVec(double* _vec, int _row)
{
	for (int i = 0; i < _row; i++)
		printf("Vector[%d] = %.1f \n", i, _vec[i]);
	printf("\n");
}

void FileoutVec1_csv(const char* _filename, double* _vec1, int _row) {
	FILE* _fp;
	_fp = fopen(_filename, "wt");
	if (_fp == NULL) {
		printf("Fail");
		return;
		}
	
	for (int i = 0; i < _row; i++) {
		fprintf(_fp, "%f\n", _vec1[i]);
	}
	fclose(_fp);
}

void FileoutVec2_csv(const char* _filename, double* _vec1,double* _vec2, int _row) {
	FILE* _fp;
	_fp = fopen(_filename, "wt");
	if (_fp == NULL) {
		printf("Fail");
		return;
	}

	for (int i = 0; i < _row; i++) {
		fprintf(_fp, "%f %f\n", _vec1[i],_vec2[i]);
	}
	fclose(_fp);
}

void gradient1D(double x[], double y[], double dydx[], int m) {
	//
	// dydx[0]    = 3-Point Forward Difference
	// dydx[1~19] = 2-Point central difference
	// dydx[20]   = 3-Point Backwared difference
	if (sizeof(x) != sizeof(y)) {
		printf("WARNING!: Length of X and Y are not equal\n");
		return;
	}
	double h = x[1] - x[0];     //time

	dydx[0] = (-3.0 * y[0] + 4.0 * y[1] - y[2]) / (2 * h);     // 3-Point Forward Difference
	for (int k = 1; k < m - 1; k++) {                        // 2-Point central Difference
		dydx[k] = ((y[k + 1] - y[k - 1]) / (2 * h));           // 3-Point Backwared difference
	}

	dydx[m - 1] = (y[m - 3] - 4.0 * y[m - 2] + 3.0 * y[m - 1]) / (2*h);

	//return dydx
	//return output value through PrintVec
}


void gradientFunc(double myFunc(const double x), double x[], double dydx[], int m) {
	
	double* y;

	y = (double*)malloc(sizeof(double) * m);
	
  for (int i =0; i<m; i++){
     y[i]= myFunc(x[i]); 	
   }

   // get gradient dydx
     gradient1D(x,y,dydx,m);
	free(y);
}
//====================================================================Integration===================================================
double IntegrateRect(double _x[], double _y[], int _m) {
	int N = _m - 1;
	double I = 0;
	for (int i = 0; i < N; i++)
		I += _y[i] * (_x[i + 1] - _x[i]);

	return I;
}

double trapz(double _x[], double _y[], int _m) {
	int N = _m - 1;

	double Tra = 0;
	for (int i = 0; i < N; i++) {
		Tra = Tra + (0.5) * ((_y[i] + _y[i + 1]) * (_x[i + 1] - _x[i]));
	}
	return Tra;
}

double Simpson13(double myFunc(const double _x), double _a, double _b, int _m) {  // (function, initial value, final value, iteration number
	
	register Count i;

	
	double h = (_b - _a) / _m;

	double result = myFunc(_a) + myFunc(_b) + (4 * myFunc(_b - h));

	LOOP(i,_m-2,1,2){
		double xi = _a + i * h;
		result = result + (4 * myFunc(xi) + 2 * myFunc(xi + h));

	}
	return result * (h / 3);

}

double Simpson38(double myFunc(const double x), double _a, double _b, int _m) {
	register Count i;
	double h      = (_b - _a) / _m;
	double result = myFunc(_a) + myFunc(_b);

	LOOP(i, _m - 1, 1, 3) {
		double xi = _a + i * h;
		result = result + 3*(myFunc(xi) + myFunc(xi + h));

	}

	LOOP(k, _m - 2, 3, 3) {
		double xi = _a + k * h;
		result = result + (2 * myFunc(xi));
	}
	
	return result * ((3*h) / 8 );
}

