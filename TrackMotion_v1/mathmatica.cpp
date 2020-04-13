#include "mathmatica.h"
//#include "stdafx.h"
using namespace std;
// General Functions
void mathmatica::matrixMultiply(double *AB, int rowAB, int colAB, const double *A, int rowA, int colA, const double *B, int rowB, int colB){
	memset(AB,0,sizeof(double)*rowAB*colAB);
	for(int i=0; i<rowA; i++){
		for(int j=0; j<colB; j++){
			for(int k=0; k<colA; k++){
				AB[i*colAB+j]+=A[i*colA+k]*B[k*colB+j];
				//AB[i][j]=AB[i][j]+A[i][k]*B[k][j];
			}
		}
	}
};

void mathmatica::matrixTrans(double *BA, const double *AB, int rowAB, int colAB){
	memset(BA,0,sizeof(double)*rowAB*colAB);
	for(int i=0; i<colAB; i++){
		for(int j=0; j<rowAB; j++){
			BA[rowAB*i+j]=AB[colAB*j+i];
		}
	}
};
//tAB[i][j]=AB[j][i];

void mathmatica::matrixInverse2(double *iA, const double *A){
	double temp[4];
	temp[0]=1.0/(A[0]*A[3]-A[1]*A[2])*A[3];
	temp[1]=-1.0/(A[0]*A[3]-A[1]*A[2])*A[1];
	temp[2]=-1.0/(A[0]*A[3]-A[1]*A[2])*A[2];
	temp[3]=1.0/(A[0]*A[3]-A[1]*A[2])*A[0];
	iA[0]=temp[0];
	iA[1]=temp[1];
	iA[2]=temp[2];
	iA[3]=temp[3];
};