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
#include"Parameter/Parameter.h"


#define Start 1	//�ŏ��̃}�X�̈ʒu

/*�O���[�vID(�������̂ݒ萔)*/
#define INDEPENDENT 0



class Field_Move_Mass;

class CollisionObject;
class Field_Object;
class BattleObject;


class HandleMediator;
class HandleMove;
class HandleBullet;
class HandleScheme;

class SchemeBox;
class Scheme;


/*
�E����L�����̃N���X�B�ړ���ԁA�e�𔭎˂���Ƃ��̏�ԁA�K�E�Z�̏�ԓ���Bridge�p�^�[���ŕێ��B
�EBuilder�p�^�[���ŃL�����̃X�e�[�^�X����
*/
class Player:public BattleObject{
public:
	int GetPredominant();
	int GetID() override;
	Player(int x,int y,Field_Move_Mass* p,int ID,float *HP,int* Pred,SchemeBox* schemeBox);
	virtual ~Player();
	void Update() override;
	void Draw() override;

	void SetPanel(Field_Move_Mass* p);
	unique_ptr < ValueState<HandleMove>> MoveState;
	unique_ptr < ValueState<HandleBullet>> BulletState;
	unique_ptr<ValueState<HandleScheme>> SchemeState;
	unique_ptr<ValueState<float>> hp;
	float MaxHP;



	/*���j�[�N�|�C���^���g���ƃG���[*/
	unique_ptr<Charging> Morale;

	unique_ptr<Reload> SBullet;
	unique_ptr<Reload> MBullet;
	unique_ptr<Reload> BBullet;

	void RecordPosition(const int FrameID); /*�����̃|�W�V����,�܂��ړ�����\��̈ʒu���p�P�b�g�ɏ�������*/



	SchemeBox* schemeBox;
	int play;
	int damage;
	int portrate;
protected:
	int ID;
private:
	static int* Predominant;

	unique_ptr<ImageBoard> img;
	float h;

	int NTPrevX, NTPrevY; 
private:
	int SchemeNumber;
	
};
