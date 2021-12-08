#include"BattleObject.h"


BattleObject::BattleObject(float posx,float posy,CollisionState* state):Field_Object(posx,posy,0.f),CollisionObject(state) {
	MoveFlag = false;
	Width = 0.f;
	Height = 0.f;
}

BattleObject::~BattleObject() {
	list<BattleObject*>::iterator itr=RecObj.begin();
	while (itr != RecObj.end()) {
		(*itr)->RefDelete(this);
		itr++;
	}
}

void BattleObject::SetPanel(Panel_Field* panel, float x, float y) {
	if (StandPos != nullptr) {
		if (StandPos->GetPredmGauge() != panel->GetPredmGauge()) {

		}
	}
	StandPos = panel;
	this->Move(x,y);
}

void BattleObject::SetPanel(Panel_Field* panel){
	if (StandPos != nullptr) {
		if (StandPos->ID != panel->ID) {
			StandPos->AddPredmGauge(this->GetPredominate());
		}
	}
	StandPos = panel;
}

void BattleObject::RefDelete(BattleObject* obj) {
	RefObj.remove(obj);
}


int BattleObject::GetPredominate() {
	return 0;
}

bool BattleObject::Siege(float *Dmg){
	(*Dmg) += 50.f;
	return true;
}


void BattleObject::ApplyStatus(){}