#include"./ChangeStatusStruct.h"


/*�t�B�[���h���ɂ���I�u�W�F�N�g�̃p�����[�^�̕ύX�́A�ꎞ�I�ɂ��̃I�u�W�F�N�g�ɕۑ�����B(�[���Ԃł̖����𐶂ݏo���Ȃ����߁B)*/
StatusBox::StatusBox(int power, float speed) {
	this->power = power;
	this->speed = speed;
	chara = nullptr;
}

void StatusBox::Reset(int power,float speed) {
	StatusBox(power, speed);
}
