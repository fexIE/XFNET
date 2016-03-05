// XFNET.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Xlayer.h"
#include "Xneuron.h"
#include "XLine.h"
#include "Xnet.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int x[] = { 1, 5, 1 };

	Xnet* net = new Xnet(x, 3);

	net->line[0]->show_W();
	net->line[1]->show_W();

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	const int len = 100;
	double _len = 1/(double)len;
	double xx[len] = { 0 };
	double y[len] = { 0 };
	double r[len] = { 0 };
	double delta = 0;

	for (int i = 0; i < len; i++){
		xx[i] = (double)i*_len;
		r[i] = sin(3.1415*xx[i] * 2);
		r[i] /= 2;
		r[i] += 0.5;
		//r[i] = 0.5;
	}

	for (int j = 0; j < 100000; j++){
		for (int i = 0; i < len; i++){
			net->backPropagation(&xx[i], &r[i], &y[i]);
		}
		delta = net->refreshNet(0.8, len);
	}	
		
		//if (j%100 == 0)			
		//	std::cout << delta << std::endl;// net->learningRate << std::endl; 
	
	double test[100] = { 0 };
	for(int i = 0; i < 100; i++){
		net->forwardPropagation(&xx[i], &test[i]);
		std::cout << test[i] << std::endl;
	}
	std::cout << std::endl;
	net->line[0]->show_W();
	net->line[1]->show_W();

	char tex;
	std::cin >> tex;
	return 0;
}
