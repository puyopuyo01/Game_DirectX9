#pragma once
//#include"Bullet/Characteristic/Characteristic.h"

/*
----------------更新パラメータの一時保存-----------------------
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
