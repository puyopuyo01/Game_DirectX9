#include"./Charging.h"


Charging::Charging(int Remain, int Max, int count) {
	this->Remain = Remain;
	this->Max = Max;
	this->counter =new Counter(count);
}

Charging::~Charging() {
	delete this->counter;
}


void Charging::Update() {
	if (Remain == Max) { return; }
	else if (Remain < Max) {
		if (this->counter->Update()) {
			Remain++;
			counter->Reset();
		}
	}
}


bool Charging::Available(int Consum) {
	if ((Remain - Consum) >= 0) { return true; }
	return false;
}

bool Charging::Consumption(int Consum) {
/* ˆø”‚ÅÁ”ï‚·‚é’l‚ğw’è‚Å‚«‚éB */
	if ((Remain - Consum) < 0) { return false; }
	else { this->Remain -= Consum; return true; }
}


int Charging::GetRemain() {
	return Remain;
}

int Charging::GetMax() {
	return Max;
}

int Charging::GetMaxCounter() {
	return this->counter->GetMaxCounter();
}

int Charging::GetRemainCounter() {
	return this->counter->GetRemainCounter();
}
