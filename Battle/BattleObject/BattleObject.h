#pragma once
#include"Battle/BattleObject/BattleObject.h"
#include"Shape.h"

class Field_Object;
class Panel_Field;

/*�Փ˔��蓙�����N���X*/
class BattleObject:public Field_Object,public CollisionObject {
public:
	BattleObject(float posx,float posy,CollisionState* state);
	~BattleObject();	/*���g�̏��������Ă���I�u�W�F�N�g�Ɏ��M�̏I����`����*/
	void RefDelete(BattleObject* obj); /*���g���Q�Ƃ���I�u�W�F�N�g��������̃I�u�W�F�N�g���폜*/
	void SetPanel(Panel_Field* panel,float x,float y);
	void SetPanel(Panel_Field* panel);
	virtual bool Siege(float* Dmg);
	virtual int GetPredominate();
	bool MoveFlag;
	Panel_Field* StandPos;

	float Width;
	float Height;
	virtual void ApplyStatus();
private:
	int x, y;
	list<BattleObject*> RecObj; /*���g�̏������I�u�W�F�N�g*/
	list<BattleObject*> RefObj; /*���M���Q�Ƃ���I�u�W�F�N�g*/
};



class Siege{}; /*
			   �U�邷��\�͂������Ă��邩�B
			   ����Ȃ������B
			   */