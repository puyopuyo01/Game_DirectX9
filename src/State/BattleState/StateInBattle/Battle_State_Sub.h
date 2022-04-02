#pragma once
#include"State/Battle_State.h"
#include"State/CharacterPanel/CutInCharacter.h"
#include"State/CharacterPanel/TextBox.h"
#include"Result/Result.h"

class SelectBox;
class SelectNextState;

class Battle_State;
class Game_State;


/*試合状態の基底クラス*/
class StateInBattle{
public:
	virtual ~StateInBattle();
	virtual StateInBattle* update(Battle_State* state);
	virtual void change_state();
	static void BaseStateSet(Game_State* state);
protected:
	static Game_State* baseState;
	string name;
};


/*試合を進行させるクラス*/
class InGame :public StateInBattle{
public:
	InGame();

	StateInBattle* update(Battle_State* state) override;

private:
	StateInBattle* NextState;
};



/*状態遷移を待機するクラス*/
class WaitingNextState : public StateInBattle {
public:
	WaitingNextState(int counter,StateInBattle* next);
	StateInBattle* update(Battle_State* state) override;

private:
	StateInBattle* NextState;

	int counter;
	int CounterMement;
};


/*演出での割り込みクラス*/
class InterputState :public StateInBattle {
/*必殺技を打ったときに、割り込みをする。 600フレーム*/
public:
	InterputState(StateInBattle* next, int TextureNumber, string name, string intro);
	~InterputState();
	StateInBattle* update(Battle_State* state) override;

private:

	void init(StateInBattle* next, int TextureNumber);
	StateInBattle* NextState;
	int PanelNum;


	unique_ptr<TextBox> text;
	int TextNum;

	int InFrame;
	int OutFrame;
	int StayFrame;
	unique_ptr<CutInCharacter> CutIn;
};

/*リザルト状態を管理するクラス*/
class Result : public StateInBattle{
public:
	Result(Player* playerHp,Player* enemyHp);
	~Result();
	StateInBattle* update(Battle_State* state) override;
private:
	string resultStr;
	int portrate;
	unique_ptr<CutInCharacter> CutIn;
	

	int PanelNum;
	int Text;

	bool wait;


	SelectBox* box;
	unique_ptr<SelectNextState> select;
};

class WaitingSelect :public StateInBattle {
public:
	WaitingSelect(SelectBox* box);
	~WaitingSelect();
	StateInBattle* update(Battle_State* state) override;
private:
	unique_ptr<SelectBox> Select;
};
