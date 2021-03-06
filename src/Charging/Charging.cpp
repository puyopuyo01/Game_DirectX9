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
	/*Remainが最大値ならチャージ(カウントダウン)しない*/
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
/* 引数で消費する値を指定できる。 */
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
