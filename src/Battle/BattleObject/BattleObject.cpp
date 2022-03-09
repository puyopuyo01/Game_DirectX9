#include"./BattleObject.h"


BattleObject::BattleObject(float posx,float posy,CollisionState* state):Field_Object(posx,posy,1.f),CollisionObject(state) {
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

	printf("BattleObject Dest!!!!\n");
}


/*派生クラスのインスタンスがどのパネルに移動したか。*/
void BattleObject::SetPanel(Panel_Field* panel, float x, float y) {
	StandPos = panel;
	this->Move(x,y);
}

void BattleObject::SetPanel(Panel_Field* panel){
	if (StandPos != nullptr) {
		/*移動先のパネルのIDが移動前のパネルと異なれば優勢ゲージを変動させる。(変動値はインスタンスによってことなる)*/
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


/*赤いパネルにたどり着いたオブジェクトはこの関数を実行。ダメージを与える。*/
bool BattleObject::Siege(float *Dmg){
	printf("Siege\n");
	(*Dmg) += 50.f;
	return true;
}


void BattleObject::ApplyStatus(){}
void BattleObject::Death(){}