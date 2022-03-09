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


/*�h���N���X�̃C���X�^���X���ǂ̃p�l���Ɉړ��������B*/
void BattleObject::SetPanel(Panel_Field* panel, float x, float y) {
	StandPos = panel;
	this->Move(x,y);
}

void BattleObject::SetPanel(Panel_Field* panel){
	if (StandPos != nullptr) {
		/*�ړ���̃p�l����ID���ړ��O�̃p�l���ƈقȂ�ΗD���Q�[�W��ϓ�������B(�ϓ��l�̓C���X�^���X�ɂ���Ă��ƂȂ�)*/
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


/*�Ԃ��p�l���ɂ��ǂ蒅�����I�u�W�F�N�g�͂��̊֐������s�B�_���[�W��^����B*/
bool BattleObject::Siege(float *Dmg){
	printf("Siege\n");
	(*Dmg) += 50.f;
	return true;
}


void BattleObject::ApplyStatus(){}
void BattleObject::Death(){}