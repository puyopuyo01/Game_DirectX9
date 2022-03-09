#pragma once
#include"./Scheme.h"
#include"State/BattleState/StateInBattle/Battle_State_Sub.h"
#include"DX_Lib/Sound/Sound.h"
#include<vector>

class StateInBattle;


/*
通信相手と処理を矛盾させないため、プレイヤーが必殺技のボタンを押したらShemeBoxに登録する。
　ローカルプレイヤーとリモートプレイヤーの必殺技ボタンを押したフレームがかぶったら
 なかったことにする。
*/
class SchemeBox {
public:
	SchemeBox();
	~SchemeBox();
	void InsertScheme(Scheme* scheme);
	StateInBattle* Update(StateInBattle* nowState);
private:
	std::vector<Scheme*> schemelist;
	Sound* SchemeSE;
};