#pragma once
//#include"Bullet/Characteristic/Characteristic.h"

/*
----------------�X�V�p�����[�^�̈ꎞ�ۑ�-----------------------
*/
class BulletCharacteristic;

class StatusBox {
public:
	StatusBox(int power, float speed);
	void Reset(int power,float speed);
	int power;
	float speed;
	BulletCharacteristic* chara;
};
