#pragma once
#include"Player/Player.h"

class SchemeBox;


/*Builder�p�^�[���ŃL�����N�^�[�N���X�������B �����_�ł͓ǂݍ��މ摜�݂̂����Ⴂ���Ȃ��B*/
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