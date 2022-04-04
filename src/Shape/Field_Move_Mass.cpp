//�X�e�[�W�p�l���̎����B�P�}�X���N���X�Ƃ��č쐬(1�}�X���X�V�����邽��)�B�C���f�b�N�X�o�b�t�@�͑����g���Ȃ��B

#include"Shape.h"
using namespace std;

int Code(float x) {
	return (x > 0) - (0 > x);
}

Field_Move_Mass* Field_Move_Mass::AllPanel[width*2][length];

int Field_Move_Mass::PredmGauge;

float Field_Move_Mass::GetSize() {
	return size;
}

/*�ʂ̃p�l������ړ����Ă����I�u�W�F�N�g�����̊֐������s���Ă���p�l���Ɉڂ��֐��B�e�[���̐����������킹�邽�߉��̃��X�g�ɓ���Ď��t���[�����炻�̃I�u�W�F�N�g���Ǘ�����*/
void Field_Move_Mass::AddObject(BattleObject* object,float x,float y) {
	ObjectMNG::GetMNG()->AddObject(object);
	this->MoveObjTemp.push_back(object);
	object->SetPanel(this,x,y);
}

void Field_Move_Mass::AddObject(BattleObject* object) {
	this->MoveObjTemp.push_back(object);
	object->SetPanel(this);
}

Field_Move_Mass::~Field_Move_Mass() {
	printf("Delete Pnael\n");
}

Field_Move_Mass::Field_Move_Mass(int x,int y,Panel_Blue* panel, float lx, float ly, float lz, float r, float g, float b, float a,float size,int ID)
	:Shape(lx,ly,lz)
{
	ent_cursor = false;
	this->ID = ID;
	this->x = x;
	this->y = y;
	this->panel = panel;
	this->size = size;
	img = make_unique<Primitive>(SQUARELINE,
								lx,ly,lz,
								size,size,
								r,g,b,a);
	

	return;
};

/*
----------------------------�}�X�ړ��֘A�̏����֐�----------------------------------

TODO:���������_���̏C��
*/
Field_Move_Mass* Field_Move_Mass::Notif(Field_Object* obj) {
	return nullptr;
}


void Field_Move_Mass::Update() {
	if (ID == PLAYER) {
		/*�J�[�\���������Ă邩���t���O�ŊǗ�*/
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


void Field_Move_Mass::MoveUpdate() {
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
				Field_Move_Mass::AllPanel[MoveY][MoveX]->AddObject(*itr);
				itr = obj.erase(itr);
			}
			continue;
		}
	}

}


void Field_Move_Mass::CollisionUpdate() {
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


void Field_Move_Mass::CollisionAll() {
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




void Field_Move_Mass::DeathUpdate() {
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


void Field_Move_Mass::ApplyStatus() {
	/*
	----------------------�I�u�W�F�N�g�̕ϐ���ύX------------------------------
	*/
	list<BattleObject*>::iterator i = obj.begin();
	while (i != obj.end()) {
		(*i)->ApplyStatus();
		i++;
	}
}

void Field_Move_Mass::MoveObject() {
	obj.merge(std::move(MoveObjTemp));
}


void Field_Move_Mass::Draw() {
	img->Draw(GetMatrix());
	list<BattleObject*>::iterator i = obj.begin();
	while (i != obj.end()) {
		if(i!=obj.end())(*i)->Draw();
		i++;
	}
	Images::GetInstance()->Reset();

}

int Field_Move_Mass::GetPredmGauge() {
	return PredmGauge;
}

int* Field_Move_Mass::GetPredAddr() { return &PredmGauge; }

void Field_Move_Mass::AddPredmGauge(int add) {
	PredmGauge += add;
}

void Field_Move_Mass::ResetPredmGauge() {
	PredmGauge = 0;
}

/*����x�}�X�A����y�}�X�ׂɃp�l�������݂��邩���肷��֐�*/
bool Field_Move_Mass::ExistPanel(int x, int y) {
	if ((this->x + x) < length && (this->x + x) >= 0 &&
		(this->y + y) < width * 2 && (this->y + y) >= 0) {
		return true;
	}
	return false;
}

/*����x�}�X�A����y�}�X�ׂ̃p�l����Ԃ��֐��B�p�l�����Ȃ����nullptr��Ԃ�*/
Field_Move_Mass* Field_Move_Mass::GetPanel(int x, int y) {
	if (this->ExistPanel(x, y)) {
		return Field_Move_Mass::AllPanel[y][x];
	}
	else {
		return nullptr;
	}
}

/*���̊֐������s���Ă���p�l����ɂ���I�u�W�F�N�g�̃��X�g�̒��̃I�u�W�F�N�gID������ID�̂��̂�S�ĕԂ��BExcept��true�Ȃ炻��ȊO��S�ĕԂ��B*/
list<BattleObject*> Field_Move_Mass::GetBattleObject(int ID, bool Except) {
	list<BattleObject*> result;
	list<BattleObject*>::iterator itr;
	itr = this->obj.begin();
	while (itr != this->obj.end()) {
		if ((*itr)->GetID() == ID && !Except) { result.push_back((*itr)); }
		else if((*itr)->GetID() != ID && Except){ result.push_back((*itr)); }
	}

	return result;
}

list<BattleObject*> Field_Move_Mass::GetBattleObject() {
	return obj;
}
