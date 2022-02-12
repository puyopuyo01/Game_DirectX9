#pragma once
#include"Player/Player.h"

class SchemeBox;


/*Builderパターンでキャラクタークラスを実装。 現時点では読み込む画像のみしか違いがない。*/
class Hero:public Player{
public:
	Hero(int x, int y, Panel_Field* p, int ID, float *HP, SchemeBox* schemeBox);

	static int PlayerTexture;
	static int Portrate;
	static int GhostTexture;
	static int GhostEyeTexture;

	static int PlayerDamage;
};

class HeroT:public Player{
public:
	HeroT(int x, int y, Panel_Field* p, int ID, float *HP, SchemeBox* schemeBox);

	static int PlayerTexture;
	static int Portrate;
	static int GhostTexture;
	static int GhostEyeTexture;

	static int PlayerDamage;
};