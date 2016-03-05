#pragma once

class XLine
{
public:
	XLine(int row, int column);//row下一层节点数 colum前一层节点数
	~XLine();

	void show_W();

	void clearDeltaW();

	double** valueW;
	double** valueY;
	double** deltaW;
	double** momentumW;//动量项
	int lineID;
	int rowSize;
	int columnSize;
};