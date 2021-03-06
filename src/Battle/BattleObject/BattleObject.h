#pragma once
#include"Battle/BattleObject/BattleObject.h"
#include"Shape.h"

class Field_Object;
class Field_Move_Mass;

/*衝突判定等を持つクラス*/
class BattleObject:public Field_Object,public CollisionObject {
public:
	BattleObject(float posx,float posy,CollisionState* state);
	virtual ~BattleObject();	/*自身の情報を持っているオブジェクトに自信の終わりを伝える*/
	void RefDelete(BattleObject* obj); /*自身を参照するオブジェクトから引数のオブジェクトを削除*/
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
	list<BattleObject*> RecObj; /*自身の情報を持つオブジェクト*/
	list<BattleObject*> RefObj; /*自身が参照するオブジェクト*/
};