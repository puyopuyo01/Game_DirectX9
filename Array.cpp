#include"Array.h"


Array::Array(int counter) {
	this->counter = counter;
}

double Array::Average() {
	list<double>::iterator itr = array.begin();
	double result = 0.f;
	while (itr != array.end()) {
		result += *itr;
		itr++;
	}
	return result/= array.size();
}

void Array::Queue(double x) {
	static int i=0;
	array.push_back(x);
	if (counter > i) {
		i++; return;
	}
	array.pop_front();
}