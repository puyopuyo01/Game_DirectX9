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


/*ゲーム状態の基底クラス(試合しているか、IP入力待ちか、遅延フレームの計測中か等)*/
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
	/*パネルは、プレイヤー側のみのパネル、敵側のみのパネル、全てのパネル等分けて保持しておく*/
	static Panel_Field* Panel_ALL[width*2][length];	
	Panel_Field* Player_Panel[PANELWIDTH][length];
	Panel_Field* Enemy_Panel[PANELWIDTH][length];
	Panel_Field* DefensePanel[2][length];	
	Panel_Blue* p_blue;

	SchemeBox* schemelist;
public:
	Battle_State(int delay);
	~Battle_State();

	static void LoadIMG();

	void Reset(); /*再度試合を行う*/
	void Abort(); /*試合を終えてIP入力待機状態へ移行する*/
	
	void UpdateUI();
	Game_State* Update() override;

private:
	ValueState<int>* Predominant;

	SchemeBox* Scheme;
	float DMGPlayerHP; /*自機の蓄積ダメージ*/
	float DMGEnemyHP; /*敵機の蓄積ダメージ*/


	/*ネットワーク周りに必要な変数*/
	int NoReach;
	int ProcessID;
	int CreateID;
	int delayFrame;
	P2P* Communication;
	KeyBox* KeyBoxes;

	bool wait;
	int WaitingFrame;


	/*試合中の状態。カットイン中、試合進行中等*/
	StateInBattle* state;

	/*暗号ファイル*/
	FileMapping* File;

	bool Finish;
	Game_State* NextState;


	/*サウンド系クラス*/
	Sound* BGM;
	Sound* DmgSE;

	


};
