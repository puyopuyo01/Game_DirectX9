#include"./Scheme.h"


Scheme::Scheme(int ID,int Texture) {
	this->ID = ID;
	this->TextureNumber = Texture;
}

/*必殺技の実行関数*/
void Scheme::Excution(){}


Enhancement::Enhancement(int ID, int pow, float speed,int* pred,int pred_inc,int TextureNumber,string name,string intro):Scheme(ID,TextureNumber){
	this->Power = pow;
	this->Speed = speed;
	this->name = name;
	this->intro = intro;
	this->pred = pred;
	this->pred_inc = pred_inc*ID;
}


/*フィールド上に存在する幽霊の強化。*/
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