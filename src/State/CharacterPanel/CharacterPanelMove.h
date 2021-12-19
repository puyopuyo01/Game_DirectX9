#pragma once
#include"./CharacterPanel.h"

class PanelMove {
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

