#pragma once
#include"Player/Player.h"

class SchemeBox;


/*Builder�p�^�[���ŃL�����N�^�[�N���X�������B �����_�ł͓ǂݍ��މ摜�݂̂����Ⴂ���Ȃ��B*/
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