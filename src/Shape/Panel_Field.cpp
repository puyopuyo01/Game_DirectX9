//�X�e�[�W�p�l���̎����B�P�}�X���N���X�Ƃ��č쐬(1�}�X���X�V�����邽��)�B�C���f�b�N�X�o�b�t�@�͑����g���Ȃ��B

#include"Shape.h"
using namespace std;

int Code(float x) {
	return (x > 0) - (0 > x);
}

Panel_Field* Panel_Field::AllPanel[width*2][length];  

int Panel_Field::PredmGauge;

float Panel_Field::GetSize() {
	return size;
}

/*�ʂ̃p�l������ړ����Ă����I�u�W�F�N�g�����̃p�l���Ɉڂ��֐��B�e�[���̐����������킹�邽�߉��̃��X�g�ɓ���Ď��t���[�����炻�̃I�u�W�F�N�g���Ǘ�����*/
void Panel_Field::AddObject(BattleObject* object,float x,float y) {
	ObjectMNG::GetMNG()->AddObject(object);
	this->MoveObjTemp.push_back(object);
	object->SetPanel(this,x,y);
}

void Panel_Field::AddObject(BattleObject* object) {
	this->MoveObjTemp.push_back(object);
	object->SetPanel(this);
}

Panel_Field::~Panel_Field() {
}

Panel_Field::Panel_Field(int x,int y,Panel_Blue* panel, float lx, float ly, float lz, float r, float g, float b, float a,float size,int ID)
	:Shape(lx,ly,lz)
{
	ent_cursor = false;
	this->ID = ID;
	this->x = x;
	this->y = y;
	this->panel = panel;
	this->size = size;
	img = make_unique<Primitive>(Primitive(SQUARELINE,
								lx,ly,lz,
								size,size,
								r,g,b,a));
	

	return;
};

/*
----------------------------�}�X�ړ��֘A�̏����֐�----------------------------------

TODO:���������_���̏C��
*/
Panel_Field* Panel_Field::Notif(Field_Object* obj) {
	return nullptr;
}


void Panel_Field::Update() {
	if (ID == PLAYER) {
		/*�J�[�\���������Ă邩���t���O�ŊǗ�����Ə������x�I�ɂ����C������*/
		if (cursor->x <= (GetLocation().x + size / 2.f) && cursor->x >= (GetLocation().x - size / 2.f) &&
			cursor->y <= (GetLocation().y + size / 2.f) && cursor->y >= (GetLocation().y - size / 2.f)) {
			/*�J�[�\�����g���ɓ����Ă�����@�J�[�\�����O�����̏���*/
			panel->notif(this, this->x, this->y);
			ent_cursor = true;
		}
		else {
			/*�J�[�\���������O�̏���*/
			if (ent_cursor) {
				ent_cursor = false;
				panel->notif(nullptr, NULL, NULL);
			}

		}
	}
	list<BattleObject*>::iterator itr;
	list<BattleObject*>::iterator i= obj.begin();
	list<BattleObject*>::iterator next;
	if (i == obj.end()) return;
/*
----------------------�X�V����(�����ŕϐ��̕ύX���͍̂s��Ȃ�)-------------------------------
*/
	while (i != obj.end()) {
		(*i)->Update();
		i++;
	}
}


void Panel_Field::MoveUpdate() {
	/*
	----------------------�I�u�W�F�N�g�̈ړ��`�F�b�N---------------------------

	�I�u�W�F�N�g�Փ˔���敪�}�X�̈ړ���=�i�I�u�W�F�N�g�̈ʒu-�}�X�����̈ʒu/�}�X�̃T�C�Y�j
											���l�̌ܓ�����int�^
	*/

	list<BattleObject*>::iterator itr;
	itr = obj.begin();
	while (itr != obj.end()) {
		float x = (*itr)->GetLocation().x - GetLocation().x;
		float y = (*itr)->GetLocation().y - GetLocation().y;
		int MoveX = (int)(x / size + (0.5*Code(x)));
		int MoveY = (int)(y / size + (0.5*Code(y)));
		if (MoveX == 0 && MoveY == 0) {
			itr++;
			continue;
		}
		else {
			MoveX += this->x; MoveY += this->y;
			if (MoveY <= (width * 2) - 1) {
				Panel_Field::AllPanel[MoveY][MoveX]->AddObject(*itr);
				itr = obj.erase(itr);
			}
			continue;
		}
	}

}


void Panel_Field::CollisionUpdate() {
	list<BattleObject*>::iterator itr;
	list<BattleObject*>::iterator i = obj.begin();
	list<BattleObject*>::iterator next;
	/*
	----------------------�}�X�ɓ����Ă���I�u�W�F�N�g�̏Փˏ���(Visitor�p�^�[�����g��) �����������_���ɂ�萮����������Ȃ����ߎg��Ȃ�----------------------
	*/
	i = obj.begin();
	while (i != obj.end()) {
		next = i;
		next++;
		for (; next != obj.end(); next++) {
			float iLeft = (*i)->GetLocation().x + ((*i)->Width / 2.f);
			float iRight = (*i)->GetLocation().x - ((*i)->Width / 2.f);
			float nextLeft = (*next)->GetLocation().x + ((*next)->Width / 2.f);
			float nextRight = (*next)->GetLocation().x - ((*next)->Width / 2.f);

			float iTop = (*i)->GetLocation().y - ((*i)->Height / 2.f);
			float iBottom = (*i)->GetLocation().y + ((*i)->Height / 2.f);
			float nextTop = (*next)->GetLocation().y - ((*next)->Height / 2.f);
			float nextBottom = (*next)->GetLocation().y + ((*next)->Height / 2.f);

			if ((iLeft > nextRight && iRight < nextLeft) && (iTop < nextBottom && iBottom > nextTop)) {
				if (next != obj.end()) {(*i)->Accept(((CollisionObject*)*next));}
			}
		}
		i++;
	}

}


void Panel_Field::CollisionAll() {
	list<BattleObject*>::iterator i = ObjectMNG::GetMNG()->AllObject.begin();
	list<BattleObject*>::iterator next;
	/*
	----------------------�S�ẴI�u�W�F�N�g�̏Փˏ���(Visitor�p�^�[�����g��)----------------------
	*/
	while (i != ObjectMNG::GetMNG()->AllObject.end()) {
		next = i;
		next++;
		for (; next != ObjectMNG::GetMNG()->AllObject.end(); next++) {
			float iLeft = (*i)->GetLocation().x + ((*i)->Width / 2.f);
			float iRight = (*i)->GetLocation().x - ((*i)->Width / 2.f);
			float nextLeft = (*next)->GetLocation().x + ((*next)->Width / 2.f);
			float nextRight = (*next)->GetLocation().x - ((*next)->Width / 2.f);

			float iTop = (*i)->GetLocation().y - ((*i)->Height / 2.f);
			float iBottom = (*i)->GetLocation().y + ((*i)->Height / 2.f);
			float nextTop = (*next)->GetLocation().y - ((*next)->Height / 2.f);
			float nextBottom = (*next)->GetLocation().y + ((*next)->Height / 2.f);

			if ((iLeft > nextRight && iRight < nextLeft) && (iTop < nextBottom && iBottom > nextTop)) {
				if (next != obj.end()) { (*i)->Accept(((CollisionObject*)*next)); }
			}
		}
		i++;
	}

}




void Panel_Field::DeathUpdate() {
	list<BattleObject*>::iterator i;
	/*
	----------------------���S�I�u�W�F�N�g�̔���----------------------------------
	*/
	i = obj.begin();
	while (i != obj.end()) {
		if ((*i)->TemporaryFlag) {
			ObjectMNG::GetMNG()->Delete(*i);
			i = obj.erase(i);
			continue;
		}
		i++;
	}

}


void Panel_Field::ApplyStatus() {
	/*
	----------------------�I�u�W�F�N�g�̕ϐ���ύX------------------------------
	*/
	list<BattleObject*>::iterator i = obj.begin();
	while (i != obj.end()) {
		(*i)->ApplyStatus();
		i++;
	}
}

void Panel_Field::MoveObject() {
	obj.merge(std::move(MoveObjTemp));
}


void Panel_Field::Draw() {
	img->Draw(GetMatrix());
	list<BattleObject*>::iterator i = obj.begin();
	while (i != obj.end()) {
		if(i!=obj.end())(*i)->Draw();
		i++;
	}
	Images::GetInstance()->Reset();

}

int Panel_Field::GetPredmGauge() {
	return PredmGauge;
}

int* Panel_Field::GetPredAddr() { return &PredmGauge; }

void Panel_Field::AddPredmGauge(int add) {
	PredmGauge += add;
}

void Panel_Field::ResetPredmGauge() {
	PredmGauge = 0;
}

/*����x�}�X�A����y�}�X�ׂɃp�l�������݂��邩���肷��֐�*/
bool Panel_Field::ExistPanel(int x, int y) {
	if ((this->x + x) < length && (this->x + x) >= 0 &&
		(this->y + y) < width * 2 && (this->y + y) >= 0) {
		return true;
	}
	return false;
}

/*����x�}�X�A����y�}�X�ׂ̃p�l����Ԃ��֐��B�p�l�����Ȃ����nullptr��Ԃ�*/
Panel_Field* Panel_Field::GetPanel(int x, int y) {
	if (this->ExistPanel(x, y)) {
		return Panel_Field::AllPanel[y][x];
	}
	else {
		return nullptr;
	}
}

/*���̃p�l����ɂ���I�u�W�F�N�g�̃��X�g�̒��̃I�u�W�F�N�gID������ID�̂��̂�S�ĕԂ��BExcept��true�Ȃ炻��ȊO��S�ĕԂ��B*/
list<BattleObject*> Panel_Field::GetBattleObject(int ID, bool Except) {
	list<BattleObject*> result;
	list<BattleObject*>::iterator itr;
	itr = this->obj.begin();
	while (itr != this->obj.end()) {
		if ((*itr)->GetID() == ID && !Except) { result.push_back((*itr)); }
		else if((*itr)->GetID() != ID && Except){ result.push_back((*itr)); }
	}

	return result;
}

list<BattleObject*> Panel_Field::GetBattleObject() {
	return obj;
}
