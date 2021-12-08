#include"./ChangeStatusStruct.h"



StatusBox::StatusBox(int power, float speed) {
	this->power = power;
	this->speed = speed;
	chara = nullptr;
}

void StatusBox::Reset(int power,float speed) {
	StatusBox(power, speed);
}
