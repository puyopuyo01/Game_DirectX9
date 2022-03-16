#pragma once
#include"DXLib_Orig.h"
#include"Battle/CollisionObject/CollisionObject.h"
#include"Battle/BattleObject/BattleObject.h"
#include"Battle/BattleDefines.h"
#include"Player_State/Player_State.h"
#include"Imageboard/ImageBoard.h"
#include"Shape.h"
#include"../State/BattleState/UI/UI.h"
#include"Player/Scheme/SchemeBox.h"
#include"Player/Scheme/Scheme.h"
#include"Charging/Charging.h"
#include"Bullet/Reload/Reload.h"


#define Start 1	//最初のマスの位置

/*グループID(無所属のみ定数)*/
#define INDEPENDENT 0



class Panel_Field;

class CollisionObject;
class Field_Object;
class BattleObject;


class HandleMediator;
class HandleMove;
class HandleBullet;
class HandleScheme;

class SchemeBox;
class Scheme;


/*
・操作キャラのクラス。移動状態、弾を発射するときの状態、必殺技の状態等をBridgeパターンで保持。
・Builderパターンでキャラのステータス実装
*/
class Player:public BattleObject{
public:
	int GetPredominant();
	int GetID() override;
	Player(int x,int y,Panel_Field* p,int ID,float *HP,int* Pred,SchemeBox* schemeBox);
	virtual ~Player();
	void Update() override;
	void Draw() override;

	void SetPanel(Panel_Field* p);
	ValueState<HandleMove>* MoveState;
	ValueState<HandleBullet>* BulletState;
	ValueState<HandleScheme>* SchemeState;
	ValueState<float>* hp;
	float MaxHP;



	/*ユニークポインタを使うとエラー*/
	Charging* Morale;

	Reload* SBullet;
	Reload* MBullet;
	Reload* BBullet;

	void RecordPosition(const int FrameID); /*自分のポジション,また移動する予定の位置をパケットに書き込む*/



	SchemeBox* schemeBox;
	int play;
	int damage;
	int portrate;
protected:
	int ID;
private:
	static int* Predominant;

	ImageBoard* img;
	float h;

	int NTPrevX, NTPrevY; 
private:
	int SchemeNumber;
	
};
