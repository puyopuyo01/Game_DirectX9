#pragma once
#include"State/Battle_State.h"
#include"State/CharacterPanel/CharacterPanel.h"
#include"State/CharacterPanel/CharacterPanelMove.h"
#include"State/CharacterPanel/TextBox.h"
#include"Result/Result.h"

class SelectBox;
class SelectNextState;

class Battle_State;
class Game_State;


/*������Ԃ̊��N���X*/
class StateInBattle{
public:
	virtual StateInBattle* update(Battle_State* state);
	virtual void change_state();
	static void BaseStateSet(Game_State* state);
protected:
	static Game_State* baseState;
	string name;
};


/*������i�s������N���X*/
class InGame :public StateInBattle{
public:
	InGame();

	StateInBattle* update(Battle_State* state) override;

private:
	StateInBattle* NextState;
};



/*��ԑJ�ڂ�ҋ@����N���X*/
class WaitingNextState : public StateInBattle {
public:
	WaitingNextState(int counter,StateInBattle* next);
	StateInBattle* update(Battle_State* state) override;

private:
	StateInBattle* NextState;

	int counter;
	int CounterMement;
};


/*���o�ł̊��荞�݃N���X*/
class InterputState :public StateInBattle {
/*�K�E�Z��ł����Ƃ��ɁA���荞�݂�����B 600�t���[��*/
public:
	InterputState(StateInBattle* next, int TextureNumber, string name, string intro);
	~InterputState();
	StateInBattle* update(Battle_State* state) override;

private:

	void init(StateInBattle* next, int TextureNumber);
	StateInBattle* NextState;
	CharacterPanel* Panel;
	int PanelNum;


	TextBox* text;
	int TextNum;

	int InFrame;
	int OutFrame;
	int StayFrame;
	PanelMove* InMove;
	PanelMove* StayMove;
	PanelMove* OutMove;
	PanelMove* State;
};

/*���U���g*/
class Result : public StateInBattle{
public:
	Result(Player* playerHp,Player* enemyHp);
	~Result();
	StateInBattle* update(Battle_State* state) override;
private:
	string resultStr;
	int portrate;

	CharacterPanel* Panel;
	PanelMove* start;
	PanelMove* InMove;
	PanelMove* StayMove;

	PanelMove* State;


	int PanelNum;
	int Text;

	bool wait;

	SelectBox* box;
	SelectNextState* select;
};

class WaitingSelect :public StateInBattle {
public:
	WaitingSelect(SelectBox* box);
	~WaitingSelect();
	StateInBattle* update(Battle_State* state) override;
private:
	SelectBox* Select;
};
