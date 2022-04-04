#pragma once
#include"Battle/BattleObject/BattleObject.h"
#include"Shape.h"

class Field_Object;
class Field_Move_Mass;

/*�Փ˔��蓙�����N���X*/
class BattleObject:public Field_Object,public CollisionObject {
public:
	BattleObject(float posx,float posy,CollisionState* state);
	virtual ~BattleObject();	/*���g�̏��������Ă���I�u�W�F�N�g�Ɏ��M�̏I����`����*/
	void RefDelete(BattleObject* obj); /*���g���Q�Ƃ���I�u�W�F�N�g��������̃I�u�W�F�N�g���폜*/
	void SetPanel(Field_Move_Mass* panel,float x,float y);
	void SetPanel(Field_Move_Mass* panel);
	virtual bool Siege(float* Dmg);
	virtual int GetPredominate();
	virtual void Death();
	bool MoveFlag;
	Field_Move_Mass* StandPos;

	float Width;
	float Height;
	virtual void ApplyStatus();
private:
	int x, y;
	list<BattleObject*> RecObj; /*���g�̏������I�u�W�F�N�g*/
	list<BattleObject*> RefObj; /*���g���Q�Ƃ���I�u�W�F�N�g*/
};