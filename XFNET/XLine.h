#pragma once

class XLine
{
public:
	XLine(int row, int column);//row��һ��ڵ��� columǰһ��ڵ���
	~XLine();

	void show_W();

	void clearDeltaW();

	double** valueW;
	double** valueY;
	double** deltaW;
	double** momentumW;//������
	int lineID;
	int rowSize;
	int columnSize;
};