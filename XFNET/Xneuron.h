#pragma once
class Xneuron
{
public:
	Xneuron(int row);
	~Xneuron();

	double PutIn(double* value, int len);

	double BackPutOut(double** value, int column, int rowSize);

	void setPoint(int layer, int Prow);

	double neuronValue;	
	double errorTerm;//²Ð²î

	int xRow;
};