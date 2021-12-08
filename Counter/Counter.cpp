#include"Counter/Counter.h"

Counter::Counter(int counter) {
	this->counter = counter;
	this->CounterMement = counter;
}


void Counter::Reset(int counter) {
	Counter::Counter(counter);
}

void Counter::Reset() {
	this->counter = this->CounterMement;
}


void Counter::AddCount(int count) {
	this->CounterMement += count;
	int Count = this->counter + count;
	if (Count > this->CounterMement) { this->counter = this->CounterMement; }
	else { this->counter = Count; }
}
void Counter::ChangeCounter(int counter) {
	this->CounterMement = counter;
	if (this->counter > counter) { this->counter = counter; }
}

int Counter::GetRemainCounter(){
	return CounterMement - counter;
}

int Counter::GetMaxCounter() {
	return CounterMement;
}

int Counter::ProcessCounter(int Counter) {
	int Remain = counter - Counter;
	if (Remain > 0) {
		counter -= Counter;
		return 0;
	}
	else if (Remain <= 0) {
		int res = Counter - counter;
		counter = 0;
		return res;
	}
}


bool Counter::Update() {
	if (this->counter == 0) {
		return true;
	}
	this->counter--;
	return false;
}