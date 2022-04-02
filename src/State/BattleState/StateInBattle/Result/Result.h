#pragma once
#include"State/BattleState/StateInBattle/Battle_State_Sub.h"


#define SELECTING 0
#define ABORT 1
#define CONTINUE 2

class StateInBattle;

class SelectBox {
	/*相手の選択を決める*/
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


	/*パネルと文字 F:続行 W:タイトルに戻る*/
	void Draw() override;
private:
	unique_ptr<Primitive> Panel;
	Font* Text;
};
