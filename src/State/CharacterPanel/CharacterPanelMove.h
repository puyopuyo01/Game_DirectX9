#pragma once
#include"./CharacterPanel.h"

class PanelMove {
	/*
	カットイン用のパネルを操作するクラス。カットイン用のパネルの移動方向、移動するまでのフレーム、移動速度決める。
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

