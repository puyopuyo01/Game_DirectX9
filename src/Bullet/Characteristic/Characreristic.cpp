#include"./Characteristic.h"
#include"Bullet/Characteristic/Shield/Collision_Shield.h"


BulletCharacteristic::BulletCharacteristic(){
}

BulletCharacteristic::~BulletCharacteristic() {
}

/*------------------------------------基底クラス----------------------------------*/
void BulletCharacteristic::Draw(Bullet* bullet) {
}

BulletCharacteristic* BulletCharacteristic::GetPrev() {
	return PrevState;
}


BulletCharacteristic* BulletCharacteristic::GetState() {
	return State;
}

BulletCharacteristic* BulletCharacteristic::ChangeCharacteristic(BulletCharacteristic* chara) {
	return chara;
}



/*---------------------------------特性を持たない-------------------------------*/

NonCharacteristic::NonCharacteristic():BulletCharacteristic(){
	PrevState = this;
	State = this;
	this->collisionState = new NormalCollisionState();
	this->bulletState = new BulletNormal();
}




/*-----------------------------------Shield------------------------------------*/

int Shield::ImageID;

void Shield::LoadIMG() {
	ImageID = Images::GetInstance()->SaveImage("Shield.png");
}

Shield::Shield(int ID,float x,float y,float size){
	this->collisionState = new CollisionShield();
	this->bulletState = new BulletNormal();
	float posY;
	posY = -(size / 2.f);
	this->board=make_unique<Primitive>(SQUARE,0.f,posY,0.f,size,size,1.f, 1.f, 1.f, 1.f);
}


void Shield::Draw(Bullet* bullet) {
	Images::GetInstance()->LoadImage(ImageID, 0);
	this->board->Draw(bullet->GetMatrix());
	Images::GetInstance()->Reset();
}