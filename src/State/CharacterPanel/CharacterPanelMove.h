#pragma once
#include"./CharacterPanel.h"

class PanelMove {
	/*
	�J�b�g�C���p�̃p�l���𑀍삷��N���X�B�J�b�g�C���p�̃p�l���̈ړ������A�ړ�����܂ł̃t���[���A�ړ����x���߂�B
	*/
public:
	PanelMove(int vector,int frame, float movement);
	virtual PanelMove* Update(CharacterPanel* panel);
	bool Finish();
	void Set(PanelMove* next);
protected:
	int vector;
	int Frame;
	float speed;
	int couter;
	PanelMove* next;
	bool finish;
};

