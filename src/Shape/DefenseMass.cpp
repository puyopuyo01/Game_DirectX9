#include"Shape.h"


DefenseMass::DefenseMass(int ID,float* Dmg,int x, int y, Panel_Blue* panel, float lx, float ly, float lz, float r, float g, float b, float a, float size)
	:Field_Move_Mass(x,y,panel,lx,ly,lz,r,g,b,a,size,ID)
{
	this->Dmg= Dmg;
	this->ID = ID;
}

void DefenseMass::AddObject(BattleObject* object) {
	this->obj.push_back(object);
	object->SetPanel(this);
}


void DefenseMass::Update() {	
	list<BattleObject*>::iterator i = obj.begin();
	if (i == obj.end()) return;
	while (i != obj.end()) {
			if ((*i)->Siege(Dmg)) {	
				ObjectMNG::GetMNG()->Delete(*i);
				i=obj.erase(i);
			}
			else {
				i++;
			}
	}

	if (obj.size() != 0) { obj.clear(); }
}


void DefenseMass::Draw() {
	img->Draw(GetMatrix());
	list<BattleObject*>::iterator i = obj.begin();
	while (i != obj.end()) {
		if (i != obj.end())(*i)->Draw();
		i++;
	}
}