#include"./Reload.h"


Reload::Reload(int Remain, int MaxBullet,int count):Charging(Remain,MaxBullet,count) {
}

Reload::~Reload() {}



void Reload::AddBullet(int bullet) {
	int addBullet = Remain + bullet;
	if (addBullet > Max) { Remain = Max; }
	else { Remain = addBullet; }
}

void Reload::ChangeMaxBullet(int MaxBullet) {this->Max = MaxBullet;}
void Reload::AddMaxBullet(int AddBullet) { this->Max += AddBullet; }
void Reload::AddCount(int Count) { this->counter->AddCount(Count); }
void Reload::ChangeCount(int Count) { this->counter->ChangeCounter(Count); }
