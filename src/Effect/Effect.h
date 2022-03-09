#pragma once
#include"Counter/Counter.h"
#include"DX_Lib/Imageboard/ImageBoard.h"
#include"Battle/DrawObject/DrawObject.h"

/*�S�ẴG�t�F�N�g������������N���X(�܂Ƃ߂ĉ摜��ǂݍ���)*/
class EffectIMG {
public:
	static void LoadImg();
};

/*
�G�t�F�N�g�̊��N���X
�e�G�t�F�N�g��Builder�p�^�[���Ŏ����B
*/
class Effect :public DrawObject {
public:
	Effect(float x,float y,int Img,int count,int vertical,int horizon);

	Effect(float x,float y,int Img,int count, int lastvertical,int vertical ,int horizon); /*�Ō�̗񂪉������邩�w��*/

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


/*�H�삪���˂��ꂽ�Ƃ��̃G�t�F�N�g*/
class SummonBullet:public Effect {
public:
	static void Init();

	SummonBullet(float x, float y, float Width, float Heigth);
	~SummonBullet();


private:
	static int ImageNumber;

};

/*�H�삪�G���U�������Ƃ��̃G�t�F�N�g*/
class BulletAttack :public Effect {
public:
	static void Init();

	BulletAttack(float x, float y, float Width, float Heigth);
	~BulletAttack();



private:
	static int ImageNumber;
};

/*�H�삪���S�����Ƃ��̃G�t�F�N�g*/
class BulletDeath :public Effect {
public:
	static void Init();

	BulletDeath(float x, float y, float Width, float Heigth);
	~BulletDeath();



private:
	static int ImageNumber;

};
