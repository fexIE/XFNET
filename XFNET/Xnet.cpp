#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "Xnet.h"

//#define learningRate 0.95

Xnet::Xnet(int *layerSize, int layerLen)
{
	layerLenth = layerLen;
	lastDeltaW[0] = 1;
	lastDeltaW[1] = 1;
	maxDeltaW = 1;
	learningRate = 1;
	if (layerLenth < 2)
		return;
	
	layer = new Xlayer*[layerLen];
	line = new XLine*[layerLen-1];

	for (int i = 0;i < layerLen;i++) {
		layer[i] = new Xlayer(*layerSize++);
	}

	inPutLayer = layer[0];
	outPutLayer = layer[layerLenth - 1];

	line[0] = inPutLayer->iniLayer(NULL, layer[1]);
	for (int i = 1;i < layerLen-1;i++) {
		line[i] = layer[i]->iniLayer(layer[i - 1], layer[i + 1]);
	}
	outPutLayer->iniLayer(layer[layerLen - 2], NULL);

	inPutValue = new double[layer[0]->layerSize];
	outPutValue = new double[outPutLayer->layerSize];

	learningRate = 1;
}


Xnet::~Xnet()
{
}

void Xnet::forwardPropagation(double* x, double* y) {	//前向传导
	inPutLayer->putIn(x, inPutLayer->layerSize);		//第一层即输入层输入数据
	inPutLayer->putOut();								//输出到下一层节点的与加权系数乘积

	Xlayer* la = inPutLayer->nextLayer;

	while (la != outPutLayer) {							//循环直到最后一层即输出层
		la->putIn();									//输入前一层加权系数乘积的和输入sigmoid函数，得到该层节点激活值
		la->putOut();
		la = la->nextLayer;								//进入下一层
	}

	outPutLayer->putIn();
	outPutLayer->getActivation(y);						//输出激活值
}

void Xnet::backPropagation(double* x, double* r, double* y) {//反向
	forwardPropagation(x, outPutValue);
	outPutLayer->cErrorTerm_In(outPutValue, r);
	outPutLayer->cErrorTerm_Out();
	Xlayer* la = outPutLayer->lastLayer;
	while (la != inPutLayer) {	
		la->cErrorTerm_In();
		la->cErrorTerm_Out();		
		la = la->lastLayer;	
	}	


	while (la != outPutLayer) {
		la->refreshDeltaW();
		la = la->nextLayer;
	}
	outPutLayer->getActivation(y);						//输出激活值
}

double Xnet::refreshNet(double learningRate, int mCount){
	Xlayer* la = inPutLayer;
	double delta = 0;
	int num = 0;
	while (la != outPutLayer) {
		delta += la->refreshLineW(learningRate, mCount);
		num++;
		la = la->nextLayer;
	}
	delta = delta / num;
	
	if (maxDeltaW < delta)
		maxDeltaW = delta;
	
	lastDeltaW[1] = lastDeltaW[0];
	lastDeltaW[0] = delta;
	return delta;
}


