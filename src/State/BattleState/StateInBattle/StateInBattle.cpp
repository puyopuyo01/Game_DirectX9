#include"Battle_State_Sub.h"

Game_State* StateInBattle::baseState;
void StateInBattle::BaseStateSet(Game_State* state) { baseState = state; }

StateInBattle* StateInBattle::update(Battle_State* state) { return nullptr; }

void StateInBattle::change_state(){}



InGame::InGame() {
	name = "InGame";
	NextState = this;
}

StateInBattle* InGame::update(Battle_State* state) {

	ObjectMNG::GetMNG()->drawObj->Update();
	int i = 0, j = 0;
	for (i = 0;i < width * 2;i++) {
		for (j = 0;j < length;j++) {
			state->Panel_ALL[i][j]->Update();
		}
	}

	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->CollisionUpdate();
		}
	}

	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->DeathUpdate();
		}
	}

	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->MoveUpdate();
		}
	}

	/*仮変数の反映に使うループ*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->MoveObject();
		}
	}

	/*仮変数の反映に使うループ*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->ApplyStatus();
		}
	}
	NextState = state->schemelist->Update(this);

	if (InGame::NextState != this) { delete this; }
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
		delete this;
		return NextState;
	}
	counter--;
	return this;
}