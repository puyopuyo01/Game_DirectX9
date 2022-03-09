#include"./CharacterPanelMove.h"


PanelMove::PanelMove(int vector,int frame, float movement) {
	this->vector = vector;
	this->Frame = frame;
	this->speed = (movement / frame)*vector;
	this->couter = frame;
	this->finish = false;
}

PanelMove* PanelMove::Update(CharacterPanel* panel){
	panel->UpdateMove(this->speed,this->vector);
	this->couter--;
	if (this->couter <= 0) { finish = true; return next; } /*指定フレーム分移動したら、次のパネル状態にする*/
	return this;
}

void PanelMove::Set(PanelMove* next) {
	this->next = next;
}

bool PanelMove::Finish() { return finish; }
