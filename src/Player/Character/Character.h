#pragma once
#include"Player/Player.h"

class SchemeBox;


/*Builderパターンでキャラクタークラスを実装。 現時点では読み込む画像のみしか違いがない。*/
class Hero:public Player{
public:
	static void LoadIMG();

	Hero(int x, int y, Field_Move_Mass* p, int ID, float *HP, int* Pred, SchemeBox* schemeBox);

	static int PlayerTexture;
	static int Portrate;
	static int GhostTexture;
	static int GhostEyeTexture;

	static int PlayerDamage;
};

class HeroT:public Player{
public:
	static void LoadIMG();

	HeroT(int x, int y, Field_Move_Mass* p, int ID, float *HP, int* Pred, SchemeBox* schemeBox);

	static int PlayerTexture;
	static int Portrate;
	static int GhostTexture;
	static int GhostEyeTexture;

	static int PlayerDamage;
};