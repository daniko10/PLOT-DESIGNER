//Extremely simple vector and matrix classes by Janusz Malinowski. 
#pragma once

#include <stdio.h>
#include <cmath>

#define M_PI 3.141

class Vector
{
public:
	double data[3];
	Vector();
	void Print(void);
	void Set(double d1, double d2);
	double GetX();
	double GetY();
};

class Matrix
{
public:
	double data[3][3];
	Matrix();
	void Print(void);
	Matrix operator*(const Matrix);
	friend Vector operator*(const Matrix, const Vector);
};

Matrix GetScaleMatrix(double w, double h, double x0, double x1, double y0, double y1);
Matrix GetRotationMatrix(double alpha);
Matrix GetTranslationMatrix(double dx, double dy);


