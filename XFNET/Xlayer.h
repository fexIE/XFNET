#pragma once

#include "Xneuron.h"
#include "XLine.h"

class  Xlayer
{
public:
	Xlayer(int size);
	XLine* iniLayer(Xlayer *lastL, Xlayer* nextLayer);
	~Xlayer();
	int putOut();
	void putIn();
	void putIn(double* value, int len);

	void cErrorTerm_Out();
	void cErrorTerm_In();
	void cErrorTerm_In(double* a, double* y);	

	void getActivation(double * y);//ȡ�øò㼤��ֵ
	void getErrorTerm(double * e);//ȡ�òв�ֵ

	void refreshDeltaW();
	double refreshLineW(double learningRate,int mCount);


	Xneuron** neuron;
	XLine* lastLineW;
	XLine* nextLineW;
	Xlayer* lastLayer;
	Xlayer* nextLayer;

	int layerSize;
	double bias;//ƫ����
};