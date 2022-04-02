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

	/*�`��݂̂��s���I�u�W�F�N�g�̍X�V�B(�e�N�X�`���̐؂�ւ���)*/
	ObjectMNG::GetMNG()->drawObj->Update();

	/*�����蔻������I�u�W�F�N�g�̍X�V�����B(���W�̈ړ���L�[���͂̔��f��)*/
	int i = 0, j = 0;
	for (i = 0;i < width * 2;i++) {
		for (j = 0;j < length;j++) {
			state->Panel_ALL[i][j]->Update();
		}
	}

	/*�I�u�W�F�N�g���m�̓����蔻�菈���B�����𐶂܂��Ȃ����߁A�����ŕύX�����p�����[�^�͂��̏����ł͔��f�����Ȃ��B*/
	state->Panel_ALL[0][0]->CollisionAll();


	/*���S�����I�u�W�F�N�g�̏����B*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->DeathUpdate();
		}
	}


	/*�I�u�W�F�N�g��������}�X����ړ�����������B�����ł͊e�}�X�̊Ǘ����X�g�ֈړ����������̃��X�g�ɓ����B*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->MoveUpdate();
		}
	}

	/*���ϐ��̔��f�Ɏg�����[�v�B�I�u�W�F�N�g���ړ������}�X�̊Ǘ����X�g�ֈڂ��B*/
	for (i = 0; i < width * 2; i++) {
		for (j = 0; j < length; j++) {
			state->Panel_ALL[i][j]->MoveObject();
		}
	}

	/*���ϐ��̔��f�Ɏg�����[�v�B�����ŃX�e�[�^�X���X�V(�e�[���ŃI�u�W�F�N�g���������鏇�Ԃ��قȂ邽��)�B*/
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