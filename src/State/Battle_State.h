#pragma once
#include"Battle/BattleDefines.h"
#include"DXLib_Orig.h"	//Field_Objectを定義
#include"Shape.h"
#include"Player.h"
#include"./BattleState/UI/UI.h"
#include<vector>
#include"NetWork/NetWork.h"
#include"Key/KeyBox.h"
#include"NetWork/Delay/Delay.h"
#include"DX_Lib/Image/FileMapping.h"
#include"BattleState/StateInBattle/Battle_State_Sub.h"
#include"Player/Scheme/SchemeBox.h"
#include"DX_Lib/Sound/Sound.h"

using namespace std;


class Panel_Blue;
class StateInBattle;
class SchemeBox;


class Game_State {
public:
	virtual Game_State* Update() { return NULL; }
	void Draw();

	int AddDrawObject(Field_Object* obj);
	void deleteObject(int index);
protected:
	vector<Field_Object*> objects;
};


/*試合を管理するクラス*/
class Battle_State :public Game_State {
public:
	static Panel_Field* Panel_ALL[width*2][length];	/*Playerの記録のみ*/
	Panel_Field* Player_Panel[PANELWIDTH][length];
	Panel_Field* Enemy_Panel[PANELWIDTH][length];
	Panel_Field* DefensePanel[2][length];	
	Panel_Blue* p_blue;

	SchemeBox* schemelist;
public:
	Battle_State(int delay);
	~Battle_State();

	void Reset();
	void Abort();
	
	void UpdateUI();
	Game_State* Update() override;

private:
	ValueState<int>* Predominant;

	SchemeBox* Scheme;
	float DMGPlayerHP;
	float DMGEnemyHP;

	int PredmGauge;
private:
	void LoadIMG();


	/*ネットワーク周り*/
	int NoReach;
	int ProcessID;
	int CreateID;
	int delayFrame;
	P2P* Communication;
	KeyBox* KeyBoxes;
	list<unique_ptr<FramePacket>> PacketQueue;
	FramePacket* LastFrame;

	bool wait;
	int WaitingFrame;


	/*バトル中の状態*/
	StateInBattle* state;

	/*暗号ファイル*/
	FileMapping* File;

	bool Finish;
	Game_State* NextState;


	Sound* BGM;

	


};


bool KeyDisassembly();