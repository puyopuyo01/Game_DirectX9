#include"./Player.h"

int* Player::Predominant;

int Player::GetID() { return this->ID; }
int Player::GetPredominant() { return (*this->Predominant); }

Player::Player(int x,int y,Panel_Field* p,int ID,float* HP,int* Pred,SchemeBox* schemeBox):BattleObject(p->GetLocation().x, p->GetLocation().y,new PlayerCollisionState(HP)){
	MaxHP = 1000.f;
	StandPos = p;
	/*通信処理で必要なため、前フレームにプレイヤーがいた位置を保持しておく。*/
	NTPrevX = StandPos->x;
	NTPrevY = StandPos->y;
	Width = SIZE/1.5f;
	Height = SIZE/1.5f;
	MoveState = new Object<HandleMove>(new IdleMove(), new NormalValue<HandleMove>());
	BulletState = new Object<HandleBullet>(new IdleBullet(), new NormalValue<HandleBullet>());
	SchemeState = new Object<HandleScheme>(new IdleScheme(), new NormalValue<HandleScheme>());
	hp = new Numerical<float>(new float(MaxHP), new NormalValue<float>(),1000.f,0.f);
	Morale = new Charging(0, 10, 200);
	/*確保位置を変えると座標ずれが発生。全部同じ位置で頂点確保して、Translation関数で調整する。*/
	img = new Primitive(SQUARE, 0.f, 0.f, -1.f,Width,Height,1.f, 1.f, 1.f, 1.f);
	this->Move(p->GetLocation().x, p->GetLocation().y);

	this->ID = ID;
	this->schemeBox = schemeBox;

	this->Predominant = Pred;
}

Player::~Player() {
	delete img;
	delete hp;
	delete MoveState;
	delete BulletState;
	delete SchemeState;
	delete Morale;

	delete SBullet;
	delete MBullet;
	delete BBullet;
	printf("Player Dest!!!\n");
}

void Player::SetPanel(Panel_Field* p) {
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