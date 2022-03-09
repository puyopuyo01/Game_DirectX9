#pragma once
#include"./../Battle_State.h"
#include"NetWork.h"
#include"./../../GameParam.h"
#include"Delay/Delay.h"
#include"./DelayMes.h"
#include"State/InputIP.h"

class Game_State;
class Font;


/*IP�A�h���X�̓��͐������������肵�ANAT�z��(UDP�z�[���p���`���O)���s���Q�[����ԁB*/
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