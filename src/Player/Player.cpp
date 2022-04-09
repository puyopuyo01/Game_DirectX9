#include"./Player.h"

int* Player::Predominant;

int Player::GetID() { return this->ID; }
int Player::GetPredominant() { return (*this->Predominant); }

Player::Player(int x,int y,Field_Move_Mass* p,int ID,float* HP,int* Pred,SchemeBox* schemeBox):BattleObject(p->GetLocation().x, p->GetLocation().y,new PlayerCollisionState(HP)){
	MaxHP = Parameter::Get()->HP;
	StandPos = p;
	/*通信処理で必要なため、前フレームにプレイヤーがいた位置を保持しておく。*/
	NTPrevX = StandPos->x;
	NTPrevY = StandPos->y;
	Width = SIZE/1.5f;
	Height = SIZE/1.5f;
	MoveState = make_unique<Object<HandleMove>>(new IdleMove(), new NormalValue<HandleMove>());
	BulletState = make_unique<Object<HandleBullet>>(new IdleBullet(), new NormalValue<HandleBullet>());
	SchemeState =  make_unique<Object<HandleScheme>>(new IdleScheme(), new NormalValue<HandleScheme>());
	hp = make_unique<Numerical<float>>(new float(MaxHP), new NormalValue<float>(),MaxHP,0.f);
	Morale = make_unique<Charging>(0, 10, 200);
	/*make_uniqueの引数で座標を指定すると座標ずれが発生。make_uniqueでは、0.fで頂点確保して、Translation関数で調整する。*/
	img = make_unique<Primitive>(SQUARE, 0.f, 0.f, -1.f,Width,Height,1.f, 1.f, 1.f, 1.f);
	this->Move(p->GetLocation().x, p->GetLocation().y);

	this->ID = ID;
	this->schemeBox = schemeBox;

	this->Predominant = Pred;
}

Player::~Player() {
}

void Player::SetPanel(Field_Move_Mass* p) {
	/*別パネルへ移動するときに呼び出される関数*/
	StandPos = p;
	NTPrevX = StandPos->x;
	NTPrevY = StandPos->y;
	this->Move(p->GetLocation().x, p->GetLocation().y);
}

void Player::Update() {
	/*各状態を更新*/
	MoveState->ChangeValue(MoveState->GetVal()->Update(this));
	BulletState->ChangeValue(BulletState->GetVal()->Update(this));
	SchemeState->ChangeValue(SchemeState->GetVal()->Update(this));
	this->Morale->Update();

}

void Player::Draw() {
	BackGroundTransparent();
	Images::GetInstance()->LoadImage(play, 0);
	img->Draw(this->GetMatrix());
	Images::GetInstance()->Reset();

}

/*
今プレイヤーが居るパネルと別のパネルをマウスでクリックしていたら、そのパネルの位置をキー入力管理クラスKeyBoxに記録。マウス操作がなければ現在いる位置を記録する。
*/
void Player::RecordPosition(const int FrameID) {
	KeyBox* key = KeyBox::GetInstance();
	if (cursor->ClickLeft()) {
		Panel_Blue* p = Panel_Blue::GetInstance();
		if (p->Location != nullptr) {
			key->SetPlayerPosition(FrameID, p->Location->x, p->Location->y);
			NTPrevX = p->x;
			NTPrevY = p->y;
			return;
		}
	}
	key->SetPlayerPosition(FrameID,NTPrevX,NTPrevY);
	printf("SET2 %d %d\n",NTPrevX,NTPrevY);
	return;
}