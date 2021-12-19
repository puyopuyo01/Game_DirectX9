#pragma once
#include<iostream>
#include <list>
#include<stdio.h>
using namespace std;

class Array {
public:
	Array(int counter);
	double Average();
	void Queue(double x);
private:
	list<double> array;
	int counter;
};
