#pragma once
#include"Counter/Counter.h"
#include"DX_Lib/Imageboard/ImageBoard.h"
#include"Battle/DrawObject/DrawObject.h"

class EffectIMG {
public:
	static void LoadImg();
};
class Effect :public DrawObject {
public:
	Effect(float x,float y,int Img,int count,int vertical,int horizon);

	Effect(float x,float y,int Img,int count, int lastvertical,int vertical ,int horizon); /*ç≈å„ÇÃóÒÇ™âΩñáÇ†ÇÈÇ©éwíË*/

	~Effect();
	void Update() override;
	void Draw() override;
protected:
	Counter* Interval;

	int AnimationHorCounter;
	int AnimationVerCounter;
	int AnimationLastVer;

	int AnimationNumHor;
	int AnimationNumVer;

	int ImgNum;
	PrimitiveUp* img;
};


class SummonBullet:public Effect {
public:
	static void Init();

	SummonBullet(float x, float y, float Width, float Heigth);
	~SummonBullet();


private:
	static int ImageNumber;

};


class BulletAttack :public Effect {
public:
	static void Init();

	BulletAttack(float x, float y, float Width, float Heigth);
	~BulletAttack();



private:
	static int ImageNumber;
};

class BulletDeath :public Effect {
public:
	static void Init();

	BulletDeath(float x, float y, float Width, float Heigth);
	~BulletDeath();



private:
	static int ImageNumber;

};
