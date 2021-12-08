#pragma once
#include"Bullet/Bullet.h"
#include"Battle/ObjectMNG/ObjectManager.h"

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
	Enhancement(int ID, int pow, float speed, int TextureNumber, string name, string intro);
	void Excution() override;

private:
	int Power;
	float Speed;
};
