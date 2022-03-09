#include"./Scheme.h"


Scheme::Scheme(int ID,int Texture) {
	this->ID = ID;
	this->TextureNumber = Texture;
}


void Scheme::Excution(){}


Enhancement::Enhancement(int ID, int pow, float speed,int* pred,int pred_inc,int TextureNumber,string name,string intro):Scheme(ID,TextureNumber){
	this->Power = pow;
	this->Speed = speed;
	this->name = name;
	this->intro = intro;
	this->pred = pred;
	this->pred_inc = pred_inc;
}

void Enhancement::Excution(){
	list<Bullet*> bullet = ObjectMNG::GetMNG()->GetBullet(ID);
	list<Bullet*>::iterator itr = bullet.begin();
	while (itr != bullet.end()) {
		if ((*itr) != nullptr) {
			(*itr)->AddPower(Power);
			(*itr)->AddSpeed(Speed);
		}
		itr++;

	}

	(*pred) += pred_inc;
}