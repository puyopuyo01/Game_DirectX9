#pragma once
#include"State/BattleState/StateInBattle/Battle_State_Sub.h"


#define SELECTING 0
#define ABORT 1
#define CONTINUE 2

class StateInBattle;

class SelectBox {
	/*����̑I�������߂�*/
public:
	SelectBox();
	void SetMySelect(int Select);
	void update();

	int PlayerSelect;
	int EnemySelect;
};

class SelectNextState :public Field_Object {
public:
	SelectNextState(float x, float y, float ScreenWidth, float ScreenHeight);
	~SelectNextState();


	/*�p�l���ƕ��� F:���s W:�^�C�g���ɖ߂�*/
	void Draw() override;
private:
	unique_ptr<Primitive> Panel;
	Font* Text;
};
