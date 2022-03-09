#pragma once
#include"Bullet/Bullet.h"
#include"Battle/ObjectMNG/ObjectManager.h"

#define LV1 2
#define LV2 4
#define LV3 5

class Bullet;


/*•KŽE‹Z‚ÌŠî’êƒNƒ‰ƒX*/
class Scheme{
public:
	Scheme(int ID,int Texture);
	int TextureNumber;
	int ID;
	virtual void Excution();

	string name;
	string intro;
};



class Enhancement :public Scheme {
public:
	Enhancement(int ID, int pow, float speed,int* pred,int pred_inc,int TextureNumber, string name, string intro);
	void Excution() override;

private:
	int Power;
	float Speed;
	int* pred;
	int pred_inc;
};
