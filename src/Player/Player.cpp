#include"./Player.h"


int Player::GetID() { return this->ID; }

Player::Player(int x,int y,Panel_Field* p,int ID,float* HP,SchemeBox* schemeBox):BattleObject(p->GetLocation().x, p->GetLocation().y,new PlayerCollisionState(HP)){
	MaxHP = 1000.f;
	StandPos = p;
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
}

void Player::SetPanel(Panel_Field* p) {
	StandPos = p;
	NTPrevX = StandPos->x;
	NTPrevY = StandPos->y;
	this->Move(p->GetLocation().x, p->GetLocation().y);
}

void Player::Update() {

	MoveState->ChangeValue(MoveState->GetVal()->Update(this));
	BulletState->ChangeValue(BulletState->GetVal()->Update(this));
	SchemeState->ChangeValue(SchemeState->GetVal()->Update(this));
	this->Morale->Update();

}

void Player::Draw() {
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x66);
	Images::GetInstance()->LoadImage(play, 0);
	img->Draw(this->GetMatrix());
	Images::GetInstance()->Reset();

}


void Player::RecordPosition(const int FrameID) {
	KeyBox* key = KeyBox::GetInstance();
	if (cursor->ClickLeft()) {
		Panel_Blue* p = Panel_Blue::GetInstance();
		if (p->Location != nullptr) {
			printf("SET1\n");
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