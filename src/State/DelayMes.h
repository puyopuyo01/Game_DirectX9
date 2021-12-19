#pragma once
#include"Battle_State.h"
#include"./NetWork/Delay/Delay.h"

class Game_State;

/*相手のDelay計測が終了したか確認、待機するクラス*/
class DelayMes:public Game_State {
public:
	DelayMes();
	Game_State* Update() override;
private:
	DelayMNG* delay;

	int WaitTime;
	int wait;
};
