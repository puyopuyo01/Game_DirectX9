#include"./Player.h"

int* Player::Predominant;

int Player::GetID() { return this->ID; }
int Player::GetPredominant() { return (*this->Predominant); }

Player::Player(int x,int y,Field_Move_Mass* p,int ID,float* HP,int* Pred,SchemeBox* schemeBox):BattleObject(p->GetLocation().x, p->GetLocation().y,new PlayerCollisionState(HP)){
	MaxHP = Parameter::Get()->HP;
	StandPos = p;
	/*�ʐM�����ŕK�v�Ȃ��߁A�O�t���[���Ƀv���C���[�������ʒu��ێ����Ă����B*/
	NTPrevX = StandPos->x;
	NTPrevY = StandPos->y;
	Width = SIZE/1.5f;
	Height = SIZE/1.5f;
	MoveState = make_unique<Object<HandleMove>>(new IdleMove(), new NormalValue<HandleMove>());
	BulletState = make_unique<Object<HandleBullet>>(new IdleBullet(), new NormalValue<HandleBullet>());
	SchemeState =  make_unique<Object<HandleScheme>>(new IdleScheme(), new NormalValue<HandleScheme>());
	hp = make_unique<Numerical<float>>(new float(MaxHP), new NormalValue<float>(),MaxHP,0.f);
	Morale = make_unique<Charging>(0, 10, 200);
	/*make_unique�̈����ō��W���w�肷��ƍ��W���ꂪ�����Bmake_unique�ł́A0.f�Œ��_�m�ۂ��āATranslation�֐��Œ�������B*/
	img = make_unique<Primitive>(SQUARE, 0.f, 0.f, -1.f,Width,Height,1.f, 1.f, 1.f, 1.f);
	this->Move(p->GetLocation().x, p->GetLocation().y);

	this->ID = ID;
	this->schemeBox = schemeBox;

	this->Predominant = Pred;
}

Player::~Player() {
}

void Player::SetPanel(Field_Move_Mass* p) {
	/*�ʃp�l���ֈړ�����Ƃ��ɌĂяo�����֐�*/
	StandPos = p;
	NTPrevX = StandPos->x;
	NTPrevY = StandPos->y;
	this->Move(p->GetLocation().x, p->GetLocation().y);
}

void Player::Update() {
	/*�e��Ԃ��X�V*/
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
���v���C���[������p�l���ƕʂ̃p�l�����}�E�X�ŃN���b�N���Ă�����A���̃p�l���̈ʒu���L�[���͊Ǘ��N���XKeyBox�ɋL�^�B�}�E�X���삪�Ȃ���Ό��݂���ʒu���L�^����B
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