#include"Player/Character/Character.h"


int Hero::PlayerTexture;
int Hero::Portrate;
int Hero::GhostTexture;
int Hero::GhostEyeTexture;

Hero::Hero(int x, int y, Panel_Field* p, int ID, float *HP, SchemeBox* schemeBox):Player(x, y, p, ID, HP, schemeBox) {
	Hero::PlayerTexture = Images::GetInstance()->SaveImage("back.png");
	Hero::Portrate = Images::GetInstance()->SaveImage("Hero.png");
	play = Hero::PlayerTexture;
	portrate = Hero::Portrate;

	SBullet = new Reload(5,5,150);
	MBullet = new Reload(4,4,160);
	BBullet = new Reload(2, 2, 180);

}


int HeroT::PlayerTexture;
int HeroT::Portrate;
int HeroT::GhostTexture;
int HeroT::GhostEyeTexture;

HeroT::HeroT(int x, int y, Panel_Field* p, int ID, float *HP, SchemeBox* schemeBox):Player(x, y, p, ID, HP, schemeBox) {
	HeroT::PlayerTexture = Images::GetInstance()->SaveImage("efore.png");
	HeroT::Portrate = Images::GetInstance()->SaveImage("Enemy.png");
	play = HeroT::PlayerTexture;
	portrate = HeroT::Portrate;

	SBullet = new Reload(5, 5, 120);
	MBullet = new Reload(4, 4, 150);
	BBullet = new Reload(2, 2, 180);

}