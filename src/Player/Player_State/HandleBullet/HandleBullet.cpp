#include"Player/Player_State/Player_State.h"
#include"Bullet/Characteristic/Characteristic.h"
#include"Parameter/Parameter.h"

IdleBullet::IdleBullet() {
	Small = false;
	Middle = false;
	Big = false;
	BulletSE =  make_unique<Sound>("Bullet.wav");
}

IdleBullet::~IdleBullet() {  }

/*プレイヤーの攻撃状態を管理するクラス(Bridgeパターンで実装)*/
HandleBullet* IdleBullet::Update(Player* player) {
	//if (player->GetID() == ENEMY) { return this; } //デバッグ用処理
	player->SBullet->Update();
	player->MBullet->Update();
	player->BBullet->Update();
	if (KeyBox::GetInstance()->updateframe == nullptr) { printf("nullです\n"); }
	const char *Key_R = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(), RB);
	const char *Key_Q = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(), QB);
	const char *Key_W = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(), WB);
	const char *Key_E = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(), EB);

	/*発射する幽霊の初期位置*/
	float x = player->StandPos->GetLocation().x;
	float y = 0.f;
	y = player->StandPos->GetLocation().y - ((player->StandPos->GetSize() / 2.f)*player->GetID());

	Parameter* pram = Parameter::Get();

	/*Qが押されていたときの処理*/
	if (strncmp(Key_Q, "1", 1) == MATCHKEYPRESS) {
		if (Small) { return this; }
		if (player->SBullet->Consumption(1)/*この攻撃に消費する弾は1*/ ) {
			BulletSE->Reset(); BulletSE->Play(false);
			Bullet* bullet = new Bullet(player->GetID(), SMALLBULLET, pram->SBulletPower, pram->SBulletSpeed, new NonCharacteristic(), x, y, SIZE / 3.f);
			player->StandPos->AddObject(bullet, x, y);
			ObjectMNG::GetMNG()->AddBullet(bullet);
			Small = true;
		}
		return this;
	}
	else { Small = false; }


	/*Wが押されていたときの処理*/
	if (strncmp(Key_W, "1", 1) == MATCHKEYPRESS) {
		if (Middle) { return this; }
		if (player->MBullet->Consumption(1))
		{
			BulletSE->Reset(); BulletSE->Play(false);
			Bullet* bullet = new Bullet(player->GetID(), MIDDLEBULLET, pram->MBulletPower, pram->MBulletSpeed, new Shield(player->GetID(), x, y, SIZE / 2.3f), x, y, SIZE / 2.3f);
			player->StandPos->AddObject(bullet, x, y);
			ObjectMNG::GetMNG()->AddBullet(bullet);
			Middle = true;
		}
		return this;
	}
	else { Middle = false; }

	/*Eが押されていたときの処理*/
	if (strncmp(Key_E, "1", 1) == MATCHKEYPRESS) {
		if (Big) { return this; }
		if (player->BBullet->Consumption(1)) {
			BulletSE->Reset(); BulletSE->Play(false);
			Bullet* bullet = new Bullet(player->GetID(), BIGBULLET, pram->BBulletPower, pram->BBulletSpeed, new NonCharacteristic(), x, y, SIZE / 1.6f);
			player->StandPos->AddObject(bullet, x, y);
			ObjectMNG::GetMNG()->AddBullet(bullet);
			Big = true;
		}
		return this;
	}
	else { Big = false; }


	if (strncmp(Key_R, "1", 1) == 0) {}

	return this;

}