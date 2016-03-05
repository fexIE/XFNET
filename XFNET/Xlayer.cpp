#include "stdafx.h"
#include "Xlayer.h"

#include <iostream>


Xlayer::Xlayer(int size){
	layerSize = size;
	neuron = new Xneuron*[size];
	for (int i = 0; i<size; i++){
		neuron[i] = new Xneuron(i);
	}
	bias = 1;
}

Xlayer::~Xlayer(){
	for (int i = 0; i<layerSize; i++){
		delete neuron[i];
	}
	delete neuron;
}

XLine* Xlayer::iniLayer(Xlayer *lastL, Xlayer* next){
	nextLayer = next;

	if (nextLayer != NULL){
		nextLineW = new XLine(nextLayer->layerSize, this->layerSize+1);//(行数，列数)
	}
	
	if (lastL != NULL) {
		lastLayer = lastL;
		lastLineW = lastLayer->nextLineW;
	}
	return nextLineW;
}

void Xlayer::getActivation(double * y) {	//取得该层激活值
	for (int i = 0;i < layerSize;i++) {
		y[i] = neuron[i]->neuronValue;
	}
}
void Xlayer::getErrorTerm(double * e) {		//取得残差值
	for (int i = 0;i < layerSize;i++) {
		*(e + i) = neuron[i]->errorTerm;
	}
}

#pragma region 前向传导
int Xlayer::putOut(){
	
	for (int r = 0; r < this->nextLineW->rowSize; r++){			
		for (int c = 0; c<this->layerSize; c++){
			nextLineW->valueY[r][c] = nextLineW->valueW[r][c] * this->neuron[c]->neuronValue;			
		}			
		nextLineW->valueY[r][this->layerSize] = nextLineW->valueW[r][this->layerSize] * this->bias;
	}	
	return 1;
}

//上一层输出的valueY每一行求和输入sigmund输出给对应该行的本层节点
void Xlayer::putIn(){
	if (lastLineW->rowSize != this->layerSize)
		return;
	for (int i = 0; i < this->layerSize; i++)
		this->neuron[i]->PutIn(this->lastLineW->valueY[i],this->lastLineW->columnSize);
}

void Xlayer::putIn(double* value, int len){
	if (len != this->layerSize)
		return;
	for (int i = 0; i < len; i++)
		this->neuron[i]->neuronValue = value[i];
}
#pragma endregion


#pragma region 反向传导
void Xlayer::cErrorTerm_In(double* a, double* y) {	//a激活值 y真实值
	for (int i = 0;i < layerSize;i++) {
		neuron[i]->errorTerm = -(y[i] - a[i])*a[i]*(1 - a[i]);
	}	
}

void Xlayer::cErrorTerm_In() {
	for (int i = 0; i < layerSize; i++) {
		neuron[i]->BackPutOut(nextLineW->valueY, i, nextLineW->rowSize);
	}
}

void Xlayer::cErrorTerm_Out(){
	for (int r = 0; r < this->lastLineW->rowSize; r++){
		for (int c = 0; c<this->lastLineW->columnSize; c++){
			lastLineW->valueY[r][c] = lastLineW->valueW[r][c] * this->neuron[r]->errorTerm;
		}
	}
}

#pragma endregion

double Xlayer::refreshLineW(double learningRate,int mCount){
	double delta = 0;
	double sumDelta = 0;
	int num = 0;
	for (int r = 0; r < this->nextLineW->rowSize; r++){
		for (int c = 0; c<this->layerSize; c++){
			delta = nextLineW->deltaW[r][c] / mCount;
			sumDelta += delta;
			num++;
			nextLineW->valueW[r][c] = nextLineW->valueW[r][c] - learningRate*(delta + 0.8*nextLineW->momentumW[r][c] +0*nextLineW->valueW[r][c]);
			nextLineW->momentumW[r][c] = delta;
		}
		delta = nextLineW->deltaW[r][this->layerSize] / mCount ;
		nextLineW->valueW[r][this->layerSize] = nextLineW->valueW[r][this->layerSize] - learningRate*(delta + 0.8*nextLineW->momentumW[r][this->layerSize]);
		nextLineW->momentumW[r][this->layerSize] = delta;
	}
	nextLineW->clearDeltaW();
	return sumDelta / num;
}

void Xlayer::refreshDeltaW(){
	for (int r = 0; r < this->nextLineW->rowSize; r++){
		for (int c = 0; c<this->layerSize; c++){
			nextLineW->deltaW[r][c] += nextLayer->neuron[r]->errorTerm * this->neuron[c]->neuronValue;
		}
		nextLineW->deltaW[r][this->layerSize] += nextLayer->neuron[r]->errorTerm;
	}
}