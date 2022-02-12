#include"./Effect.h"

int SummonBullet::ImageNumber;
int BulletAttack::ImageNumber;
int BulletDeath::ImageNumber;

void EffectIMG::LoadImg() {
	SummonBullet::Init();
	BulletAttack::Init();
	BulletDeath::Init();
}

Effect::Effect(float x,float y,int Img,int count, int vertical, int horizon) :DrawObject(x, y) {
	ImgNum = Img;
	this->Interval = new Counter(count);
	AnimationVerCounter = 0;
	AnimationHorCounter = 0;

	AnimationNumHor = horizon;
	AnimationNumVer = vertical;
	AnimationLastVer = vertical;
}

Effect::Effect(float x,float y,int Img,int count, int lastvertical,int vertical ,int horizon) :DrawObject(x, y) {
	ImgNum = Img;
	this->Interval = new Counter(count);
	AnimationVerCounter = 0;
	AnimationHorCounter = 0;

	AnimationNumHor = horizon;
	AnimationNumVer = vertical;
	AnimationLastVer = lastvertical;
}


Effect::~Effect() {
	delete Interval;
	delete img;
}

void Effect::Update() {
	if (AnimationHorCounter >= AnimationNumHor) { 
		if (AnimationLastVer < AnimationVerCounter) { this->Death = true; return; }

	}
	if (Interval->Update()) { 
		Interval->Reset(); 
		AnimationVerCounter++;
		if (AnimationVerCounter >= AnimationNumVer && AnimationHorCounter < AnimationNumHor) { 
			AnimationVerCounter = 0; AnimationHorCounter++; 
		}
		if (AnimationVerCounter != AnimationNumVer) { img->SetUV((float)AnimationVerCounter, (float)AnimationHorCounter); }
	}
	return;

}


void Effect::Draw(){
	Images::GetInstance()->LoadImage(ImgNum, 0);
	img->Draw(this->GetMatrix());
	Images::GetInstance()->Reset();
}



SummonBullet::SummonBullet(float x, float y, float Width, float Heigth):Effect(x,y,ImageNumber,1,10,0) {
	img = new PrimitiveUp(SQUARE, x, y, 0.f,Width+5.f, Heigth+5.f,
		1.f, 1.f, 1.f, 1.f
		, 10.f, 1.f);
	img->SetUV(0.f, 0.f);
}

SummonBullet::~SummonBullet(){}

void SummonBullet::Init() {
	ImageNumber = Images::GetInstance()->SaveImage("SummonBullet.png");
}


BulletAttack::BulletAttack(float x, float y, float Width, float Heigth) :Effect(x, y,ImageNumber,1,3,5,1) {
	img = new PrimitiveUp(SQUARE, x, y, 0.f, Width+5.f, Heigth+5.f,
		1.f, 1.f, 1.f, 1.f
		, 5.f, 2.f);
	img->SetUV(0.f, 0.f);
}

BulletAttack::~BulletAttack(){}

void BulletAttack::Init() {
	ImageNumber = Images::GetInstance()->SaveImage("BulletAttack.png");
}



BulletDeath::BulletDeath(float x, float y, float Width, float Heigth) :Effect(x, y, ImageNumber, 1, 8, 0) {
	img = new PrimitiveUp(SQUARE, x, y, 0.f, Width+5.f, Heigth+5.f,
		1.f, 1.f, 1.f, 1.f
		, 8.f, 1.f);
	img->SetUV(0.f, 0.f);
}

BulletDeath::~BulletDeath() {}

void BulletDeath::Init() {
	ImageNumber = Images::GetInstance()->SaveImage("BulletDeath.png");
}


