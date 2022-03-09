#pragma once
#include"Counter/Counter.h"
#include"DX_Lib/Imageboard/ImageBoard.h"
#include"Battle/DrawObject/DrawObject.h"

/*全てのエフェクトを初期化するクラス(まとめて画像を読み込む)*/
class EffectIMG {
public:
	static void LoadImg();
};

/*
エフェクトの基底クラス
各エフェクトはBuilderパターンで実装。
*/
class Effect :public DrawObject {
public:
	Effect(float x,float y,int Img,int count,int vertical,int horizon);

	Effect(float x,float y,int Img,int count, int lastvertical,int vertical ,int horizon); /*最後の列が何枚あるか指定*/

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


/*幽霊が発射されたときのエフェクト*/
class SummonBullet:public Effect {
public:
	static void Init();

	SummonBullet(float x, float y, float Width, float Heigth);
	~SummonBullet();


private:
	static int ImageNumber;

};

/*幽霊が敵を攻撃したときのエフェクト*/
class BulletAttack :public Effect {
public:
	static void Init();

	BulletAttack(float x, float y, float Width, float Heigth);
	~BulletAttack();



private:
	static int ImageNumber;
};

/*幽霊が死亡したときのエフェクト*/
class BulletDeath :public Effect {
public:
	static void Init();

	BulletDeath(float x, float y, float Width, float Heigth);
	~BulletDeath();



private:
	static int ImageNumber;

};
