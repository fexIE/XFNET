#include "stdafx.h"
#include "XLine.h"

#include <stdio.h>
#include <iostream>
#include <time.h>


XLine::XLine(int row, int column){//row下一层节点数 colum前一层节点数
	rowSize = row;
	columnSize = column;
	valueW = new double*[row];
	valueY = new double*[row];
	deltaW = new double*[row];
	momentumW = new double*[row];
	srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子
	for (int i = 0; i<row; i++) {
		valueW[i] = new double[column];
		valueY[i] = new double[column];
		deltaW[i] = new double[column];
		momentumW[i] = new double[column];
		for (int j = 0; j<columnSize; j++){
			valueW[i][j] = (double)rand() / 3276800;
			valueY[i][j] = 0;
			deltaW[i][j] = 0;
			momentumW[i][j] = 0;
		}
	}
}
XLine::~XLine(){
	for (int i = 0; i < columnSize; i++){
		delete[]valueW[i];
		delete[]valueY[i];
	}
	delete[]valueW;
	delete[]valueY;
}

void XLine::show_W(){
	for (int i = 0; i<rowSize; i++){
		for (int j = 0; j<columnSize; j++){
			std::cout << valueW[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void XLine::clearDeltaW(){
	for (int i = 0; i<rowSize; i++) {
		for (int j = 0; j<columnSize; j++){
			deltaW[i][j] = 0;
		}
	}
}