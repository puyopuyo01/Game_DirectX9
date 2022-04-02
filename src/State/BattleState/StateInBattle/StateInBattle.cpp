#include"Battle_State_Sub.h"

Game_State* StateInBattle::baseState;
void StateInBattle::BaseStateSet(Game_State* state) { baseState = state; }
StateInBattle::~StateInBattle(){}
StateInBattle* StateInBattle::update(Battle_State* state) { return nullptr; }

void StateInBattle::change_state(){}



InGame::InGame() {
	name = "InGame";
	NextState = this;
}

StateInBattle* InGame::update(Battle_State* state) {

	/*描画のみを行うオブジェクトの更新。(テクスチャの切り替え等)*/
	ObjectMNG::GetMNG()->drawObj->Update();

	/*当たり判定を持つオブジェクトの更新処理。(座標の移動やキー入力の反映等)*/
	int i = 0, j = 0;
	for (i = 0;i < width * 2;i++) {
		for (j = 0;j < length;j++) {
			state->Panel_ALL[i][j]->Update();
		}
	}

	/*オブジェクト同士の当たり判定処理。矛盾を生ませないため、ここで変更したパラメータはこの処理では反映させない。*/
	state->Panel_ALL[0][0]->CollisionAll();


	/*死亡したオブジェクトの処理。*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->DeathUpdate();
		}
	}


	/*オブジェクトが今居るマスから移動したか判定。ここでは各マスの管理リストへ移動させず仮のリストに入れる。*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->MoveUpdate();
		}
	}

	/*仮変数の反映に使うループ。オブジェクトを移動したマスの管理リストへ移す。*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->MoveObject();
		}
	}

	/*仮変数の反映に使うループ。ここでステータスを更新(各端末でオブジェクトを処理する順番が異なるため)。*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->ApplyStatus();
		}
	}
	NextState = state->schemelist->Update(this);

	return NextState;
}




WaitingNextState::WaitingNextState(int counter, StateInBattle* next) {
	name = "Waiting";
	this->counter = counter;
	this->CounterMement = counter;
	this->NextState = next;
}

StateInBattle* WaitingNextState::update(Battle_State* state) {
	if (counter <= 0) {
		return NextState;
	}
	counter--;
	return this;
}