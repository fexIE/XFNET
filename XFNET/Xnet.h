#pragma once

#include "Xlayer.h"
class Xnet
{
public:
	Xnet(int *layerSize,int layerLen);
	~Xnet();

	void forwardPropagation(double* x,double* y);
	void backPropagation(double* x, double* r, double *y);
	double refreshNet(double learningRate, int mCount);

	int layerLenth;

	double maxDeltaW;
	double lastDeltaW[2];
	double learningRate;

	int time;

	double* inPutValue;
	double* outPutValue;
	Xlayer** layer;
	Xlayer* outPutLayer;// ‰≥ˆ≤„
	Xlayer* inPutLayer;// ‰»Î≤„
	XLine** line;

};

