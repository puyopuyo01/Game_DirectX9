#pragma once
#include"Battle_State.h"
#include"./NetWork/Delay/Delay.h"

class Game_State;

/*�����Delay�v�����I���������m�F�A�ҋ@����N���X*/
class DelayMes:public Game_State {
public:
	DelayMes();
	Game_State* Update() override;
private:
	DelayMNG* delay;

	int WaitTime;
	int wait;
};
