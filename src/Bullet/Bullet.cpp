#include"./Bullet.h"

int Bullet::Body;
int Bullet::Eye;

int Bullet::GetBulletID(){ return BulletID; }
int Bullet::GetID() { return this->GroupID; }
int Bullet::GetObjectID() { return BULLET; }
int Bullet::GetPow() { return *(power->GetVal()); }
float Bullet::GetSpeed() { return *(speed->GetVal()); }


/*更新されたパラメータは仮変数に保持*/
void Bullet::AddPower(int pow) { status->power += pow; }
void Bullet::AddSpeed(float speed){ status->speed += speed; }

int Bullet::GetTexture() { return Body; }

void Bullet::Init() {
	/*画像を読み込む*/
	Body = Images::GetInstance()->SaveImage("body.png");
	Eye = Images::GetInstance()->SaveImage("eye.png");
	Shield::LoadIMG();
}

/*UI用コンストラクタ。ステータスを設定する必要がない。*/
Bullet::Bullet(int GroupID, int BulletID, float posx, float posy, float size) :BattleObject(posx, posy, nullptr) {
	board = make_unique<Primitive>(SQUARE, 0.f, 0.f, 0.f, size, size, 1.f, 1.f, 1.f, 1.f);
	eye = make_unique<Primitive>(SQUARE, 0.f, 0.f, 0.f, size, size, 1.f, 1.f, 1.f, 1.f);
	if (BulletID == MIDDLEBULLET) {
		charac = make_unique<Shield>(GroupID,posx,posy, SIZE / 2.3f);
	}
	else {
		charac = make_unique<NonCharacteristic>();
	}
	state = make_unique<BulletNormal>();
	this->Move(posx, posy);
}
/*speedは、1マス移動するのにかかるフレーム数を指定*/
Bullet::Bullet(int GroupID,int BulletID,int power,float speed,BulletCharacteristic* BState,float posx,float posy,float size):BattleObject(posx,posy,BState->collisionState){
	this->Width = size;
	this->Height = size;
	this->BulletID = BulletID;
	this->GroupID = GroupID;
	this->power=make_unique<Numerical<int>>(new int(power), new NormalValue<int>(), 99, 0);
	float speedTemp = (FRAMEPERSEC / speed) *SIZE;
	this->speed = make_unique<Numerical<float>>(new float(speedTemp), new NormalValue<float>(), 1000.f, 0);
	state=unique_ptr<BulletState>(BState->bulletState);
	charac=unique_ptr<BulletCharacteristic>(std::move(BState));
	board=make_unique<Primitive>(SQUARE, 0.f, 0.f, 0.f,this->Width,this->Height, 1.f, 1.f, 1.f, 1.f);
	this->Move(posx,posy);
	speedx = 0.f;
	this->vec = GroupID;
	eye = make_unique<Primitive>(SQUARE, 0.f, 0.f, 0.f,this->Width,this->Height, 1.f, 1.f, 1.f, 1.f);
	if (GroupID == PLAYER) { this->Rot(180.f); }
	status = make_unique<StatusBox>(*(this->power->GetVal()), *(this->speed->GetVal()));
	ObjectMNG::GetMNG()->drawObj->AddObject(new SummonBullet(posx,posy,size,size));
}

Bullet::~Bullet() {
	printf("Bullet Dest!!!\n");
}



int Bullet::GetPredominate() {	
	return this->GroupID; 
}


/*相手のHPが減るマスに到達したときの処理。ダメージ量は「強さ」のパラメータに依存する。また攻撃用のエフェクト(DrawObject)を生成。*/
bool Bullet::Siege(float* Dmg) {
	ObjectMNG::GetMNG()->drawObj->AddObject(new BulletAttack(this->GetLocation().x, this->GetLocation().y,
										Width, Height));
	(*Dmg) += this->GetPow()*10;	//ダメージ量 = 強さ×10
	return true;
}


/*死亡処理。死亡用のエフェクト(DrawObject)を生成。*/
void Bullet::Death() {
	if (!this->TemporaryFlag) { return; }
	ObjectMNG::GetMNG()->drawObj->AddObject(new BulletDeath(this->GetLocation().x, this->GetLocation().y,
		Width, Height));
}

/*パラメータの変更を更新する。*/
void Bullet::ApplyStatus() {
	this->power->ChangeValue(status->power);
	this->speed->ChangeValue(status->speed);
	if (status->chara != nullptr) {
		this->charac.reset(status->chara);
		this->ChangeState(charac->collisionState);
	}
	status->Reset(*(this->power->GetVal()), *(this->speed->GetVal()));
}

void Bullet::Update() {
	state->Update(this,this->vec);
}

void Bullet::Draw(){
	if (!state->Draw(this)) { return; }
	BackGroundTransparent();
	Images::GetInstance()->LoadImage(Body, 0);
	board->Draw(this->GetMatrix());
	Images::GetInstance()->Reset();
	Images::GetInstance()->LoadImage(Eye, 0);
	eye->Draw(this->GetMatrix());
	Images::GetInstance()->Reset();

	charac->Draw(this);
}


