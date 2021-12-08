#pragma once
#include"DXLib_Orig.h"
#include"Value_State.h"
#include"CollisionState.h"
#include"Battle/ChangeStatusStruct.h"

class CollisionState;

class CollisionObject {
public:
	CollisionObject(CollisionState* state);
	~CollisionObject() ;
	/*�ŗL�̔\�́B�l��ύX����ꍇ�́A�t���O�Ȃǂ����Ă�悤�ɂ��āA�Ō�̍X�V�����ł܂Ƃ߂čs���B*/
	virtual void Ability(CollisionObject* HitObj);	 //virtual�̕K�v�Ȃ������B
	virtual void ChangeState(CollisionState* newState);
	virtual void AddPower(int pow);
	virtual void AddSpeed(float speed);

	/*
	Accept�́A�o�g���X�e�[�g����Ăяo�����֐��B���������I�u�W�F�N�g�ɒʒm����B
	Visit�͓��Ă�ꂽ�I�u�W�F�N�g�B���g�̏����̂ݍs���B
	 */
	void Accept(CollisionObject* HitObj);
	void Visit(CollisionObject* HitObj);



	/*
	�I�u�W�F�N�g����̒l�̓I�[�o�[���C�h�Ŏ��o���B
	*/
	virtual int GetID();// { return 0; }
	virtual int GetObjectID();
	virtual int GetPow() { return 100; }
	virtual float GetSpeed() { return 0.f; }
	/*
	���̎��S�t���O�B��������Ȃ��Ə����ɂ���ẮA�ʐM����Ƃ̖����𐶂ށB
	*/
	bool TemporaryFlag;
private:
	unique_ptr<CollisionState> CollisionBridge;
	void BaseCollision(CollisionObject* HitObj);

};



