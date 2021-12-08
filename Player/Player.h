#pragma once
#include"DXLib_Orig.h"
#include"Battle/CollisionObject/CollisionObject.h"
#include"Battle/BattleObject/BattleObject.h"
#include"Battle/BattleDefines.h"
#include"Player_State/Player_State.h"
#include"Imageboard/ImageBoard.h"
#include"Shape.h"
#include"../State/BattleState/UI/UI.h"
#include"Player/Scheme/SchemeBox.h"
#include"Player/Scheme/Scheme.h"
#include"Charging/Charging.h"
#include"Bullet/Reload/Reload.h"

/*
�EBuilder�p�^�[���ŃL�����̃X�e�[�^�X����
*/
#define Start 1	//�ŏ��̃}�X�̈ʒu

/*�O���[�vID(�������̂ݒ萔)*/
#define INDEPENDENT 0



class Panel_Field;

class CollisionObject;
class Field_Object;
class BattleObject;


class HandleMediator;
class HandleMove;
class HandleBullet;
class HandleScheme;

class SchemeBox;
class Scheme;

class Player:public BattleObject{
public:
	int GetID() override;
	Player(int x,int y, Panel_Field* p,int ID,float *HP,SchemeBox* schemeBox);
	~Player();
	void Update() override;
	void Draw() override;
	ValueState<HandleMove>* MoveState;
	ValueState<HandleBullet>* BulletState;
	ValueState<HandleScheme>* SchemeState;
	ValueState<float>* hp;
	float MaxHP;

	//unique_ptr<Charging> Morale;
	/*���j�[�N�|�C���^���g���ƃG���[*/
	Charging* Morale;

	Reload* SBullet;
	Reload* MBullet;
	Reload* BBullet;

	void RecordPosition(const int FrameID); /*�����̃|�W�V����,�܂��ړ�����\��̈ʒu���p�P�b�g�ɏ�������*/



	SchemeBox* schemeBox;
	int portrate;
protected:
	int ID;
	int play;
private:

	ImageBoard* img;
	float h;

	int NTPrevX, NTPrevY; 
private:
	int SchemeNumber;
	
};
