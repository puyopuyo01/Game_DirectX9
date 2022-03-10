#pragma once
#include"Battle/BattleDefines.h"
#include"DXLib_Orig.h"	//Field_Object���`
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


/*�Q�[����Ԃ̊��N���X(�������Ă��邩�AIP���͑҂����A�x���t���[���̌v��������)*/
class Game_State {
public:
	virtual Game_State* Update() { return NULL; }
	void Draw();

	int AddDrawObject(Field_Object* obj);
	void deleteObject(int index);
protected:
	vector<Field_Object*> objects;
};


/*�������Ǘ�����N���X*/
class Battle_State :public Game_State {
public:
	/*�p�l���́A�v���C���[���݂̂̃p�l���A�G���݂̂̃p�l���A�S�Ẵp�l���������ĕێ����Ă���*/
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

	void Reset(); /*�ēx�������s��*/
	void Abort(); /*�������I����IP���͑ҋ@��Ԃֈڍs����*/
	
	void UpdateUI();
	Game_State* Update() override;

private:
	ValueState<int>* Predominant;

	SchemeBox* Scheme;
	float DMGPlayerHP; /*���@�̒~�σ_���[�W*/
	float DMGEnemyHP; /*�G�@�̒~�σ_���[�W*/


	/*�l�b�g���[�N����ɕK�v�ȕϐ�*/
	int NoReach;
	int ProcessID;
	int CreateID;
	int delayFrame;
	P2P* Communication;
	KeyBox* KeyBoxes;

	bool wait;
	int WaitingFrame;


	/*�������̏�ԁB�J�b�g�C�����A�����i�s����*/
	StateInBattle* state;

	/*�Í��t�@�C��*/
	FileMapping* File;

	bool Finish;
	Game_State* NextState;


	/*�T�E���h�n�N���X*/
	Sound* BGM;
	Sound* DmgSE;

	


};
