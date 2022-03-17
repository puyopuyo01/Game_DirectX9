#include"Player/Character/Character.h"


int Hero::PlayerTexture;
int Hero::Portrate;
int Hero::GhostTexture;
int Hero::GhostEyeTexture;
int Hero::PlayerDamage;


void Hero::LoadIMG() {
	Hero::PlayerTexture = Images::GetInstance()->SaveImage("back.png");
	Hero::Portrate = Images::GetInstance()->SaveImage("Hero.png");
	PlayerDamage = Images::GetInstance()->SaveImage("HeroD.png");
}

/*ローカルプレイヤ側のテクスチャ*/
Hero::Hero(int x, int y, Panel_Field* p, int ID, float *HP,int* Pred ,SchemeBox* schemeBox):Player(x, y, p, ID, HP,Pred ,schemeBox) {
	play = Hero::PlayerTexture;
	portrate = Hero::Portrate;
	damage = Hero::PlayerDamage;

	SBullet = new Reload(5,5,70);
	MBullet = new Reload(4,4,120);
	BBullet = new Reload(2, 2, 180);

}


int HeroT::PlayerTexture;
int HeroT::Portrate;
int HeroT::GhostTexture;
int HeroT::GhostEyeTexture;
int HeroT::PlayerDamage;

void HeroT::LoadIMG() {
	HeroT::PlayerTexture = Images::GetInstance()->SaveImage("efore.png");
	HeroT::Portrate = Images::GetInstance()->SaveImage("Enemy.png");
	PlayerDamage = Images::GetInstance()->SaveImage("EnemyD.png");
}


/*リモートプレイヤ(通信相手)側のテクスチャ*/
HeroT::HeroT(int x, int y, Panel_Field* p, int ID, float *HP, int* Pred, SchemeBox* schemeBox):Player(x, y, p, ID, HP,Pred, schemeBox) {
	damage = HeroT::PlayerDamage;
	play = HeroT::PlayerTexture;
	portrate = HeroT::Portrate;
	SBullet = new Reload(5,5,70);
	MBullet = new Reload(4,4,120);
	BBullet = new Reload(2,2,180);

}