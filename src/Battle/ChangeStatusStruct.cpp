#include"./ChangeStatusStruct.h"


/*フィールド内にいるオブジェクトのパラメータの変更は、一時的にこのオブジェクトに保存する。(端末間での矛盾を生み出さないため。)*/
StatusBox::StatusBox(int power, float speed) {
	this->power = power;
	this->speed = speed;
	chara = nullptr;
}

void StatusBox::Reset(int power,float speed) {
	StatusBox(power, speed);
}
