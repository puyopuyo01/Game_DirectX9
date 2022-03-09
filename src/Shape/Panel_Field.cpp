//ステージパネルの実装。１マスずつクラスとして作成(1マスずつ更新させるため)。インデックスバッファは多分使えない。

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

/*別のパネルから移動してきたオブジェクトをこのパネルに移す関数。各端末の整合性を合わせるため仮のリストに入れて次フレームからそのオブジェクトを管理する*/
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
----------------------------マス移動関連の処理関数----------------------------------

TODO:浮動小数点問題の修正
*/
Panel_Field* Panel_Field::Notif(Field_Object* obj) {
	return nullptr;
}


void Panel_Field::Update() {
	if (ID == PLAYER) {
		/*カーソルが入ってるかをフラグで管理すると処理速度的にいい気がする*/
		if (cursor->x <= (GetLocation().x + size / 2.f) && cursor->x >= (GetLocation().x - size / 2.f) &&
			cursor->y <= (GetLocation().y + size / 2.f) && cursor->y >= (GetLocation().y - size / 2.f)) {
			/*カーソルが枠内に入っていたら　カーソルが外→内の処理*/
			panel->notif(this, this->x, this->y);
			ent_cursor = true;
		}
		else {
			/*カーソルが内→外の処理*/
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
----------------------更新処理(ここで変数の変更自体は行わない)-------------------------------
*/
	while (i != obj.end()) {
		(*i)->Update();
		i++;
	}
}


void Panel_Field::MoveUpdate() {
	/*
	----------------------オブジェクトの移動チェック---------------------------

	オブジェクト衝突判定区分マスの移動量=（オブジェクトの位置-マス中央の位置/マスのサイズ）
											を四捨五入したint型
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
	----------------------マスに入っているオブジェクトの衝突処理(Visitorパターンを使う) ※浮動小数点問題により整合性が合わないため使わない----------------------
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
	----------------------全てのオブジェクトの衝突処理(Visitorパターンを使う)----------------------
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
	----------------------死亡オブジェクトの判定----------------------------------
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
	----------------------オブジェクトの変数を変更------------------------------
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

/*引数xマス、引数yマス隣にパネルが存在するか判定する関数*/
bool Panel_Field::ExistPanel(int x, int y) {
	if ((this->x + x) < length && (this->x + x) >= 0 &&
		(this->y + y) < width * 2 && (this->y + y) >= 0) {
		return true;
	}
	return false;
}

/*引数xマス、引数yマス隣のパネルを返す関数。パネルがなければnullptrを返す*/
Panel_Field* Panel_Field::GetPanel(int x, int y) {
	if (this->ExistPanel(x, y)) {
		return Panel_Field::AllPanel[y][x];
	}
	else {
		return nullptr;
	}
}

/*このパネル上にあるオブジェクトのリストの中のオブジェクトIDが引数IDのものを全て返す。Exceptがtrueならそれ以外を全て返す。*/
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
