#include "stdafx.h"
#include "Xneuron.h"
#include <math.h>

inline double func(double x){
	return 1/(1 + exp(-x));
}

inline double D_func(double a){
	return a*(1 - a);
}

Xneuron::Xneuron(int row){
	xRow = row;
	neuronValue = 0;

}

Xneuron::~Xneuron(){

}

double Xneuron::PutIn(double* value, int len){
	double oo = 0;
	for (int i = 0; i<len; i++){
		oo += value[i];
	}	
	neuronValue = func(oo);
	return neuronValue;
}

double Xneuron::BackPutOut(double** value, int column, int rowSize){//矩阵第column列求和
	double oo = 0;
	for (int i = 0; i<rowSize; i++){
		oo += value[i][column];
	}
	errorTerm = oo * D_func(neuronValue);
	return errorTerm;
}

void Xneuron::setPoint(int layer, int Prow){
	return;
}

