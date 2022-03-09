#pragma once
#include"Battle_State.h"
#include"./NetWork/Delay/Delay.h"

class Game_State;

/*’x‰„Œv‘ª‚·‚éƒNƒ‰ƒX*/
class DelayMes:public Game_State {
public:
	DelayMes();
	Game_State* Update() override;
private:
	DelayMNG* delay;

	int WaitTime;
	int wait;
};
