#pragma once
#include"./../Battle_State.h"
#include"NetWork.h"
#include"./../../GameParam.h"
#include"Delay/Delay.h"
#include"./DelayMes.h"
#include"State/InputIP.h"

class Game_State;
class Font;


/*IPアドレスの入力成功したか判定し、NAT越え(UDPホールパンチング)を行うゲーム状態。*/
class EstablishCommunicate :public Game_State {
public:
	EstablishCommunicate(char *ip);
	~EstablishCommunicate();
	Game_State* Update() override;
private:
	char *ip;
	P2P* p2p;

	int InitRes;
};