#pragma once
//#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "math.h"
#include "windows.h"
#include <iostream>
#include <string>
#include <tchar.h>

using namespace std;

class mathmatica{
public:
	// AB=A*B
	static void matrixMultiply(double *AB, int rowAB, int colAB, const double *A, int rowA, int colA, const double *B, int rowB, int colB);
	// BA=AB'
	static void matrixTrans(double *BA, const double *AB, int rowAB, int colAB);
	// iA= A^-1
	static void matrixInverse2(double *iA, const double *A);
};