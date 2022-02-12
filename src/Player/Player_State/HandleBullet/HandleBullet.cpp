#include"Player/Player_State/Player_State.h"
#include"Bullet/Characteristic/Characteristic.h"

IdleBullet::IdleBullet() {
	Small = false;
	Middle = false;
	Big = false;
}


/*プレイヤーの攻撃状態を管理するクラス(Bridgeパターンで実装)*/
HandleBullet* IdleBullet::Update(Player* player) {
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

	float x = player->StandPos->GetLocation().x;
	float y = 0.f;
	y = player->StandPos->GetLocation().y - ((player->StandPos->GetSize() / 2.f)*player->GetID());

	if (strncmp(Key_Q, "1", 1) == 0) {
		if (Small) { return this; }
		if (player->SBullet->Consumption(1)/*この攻撃に消費する弾は1*/ ) {
			Bullet* bullet = new Bullet(player->GetID(), SMALLBULLET, 3, 10.f, new NonCharacteristic(), x, y, SIZE / 3.f);
			player->StandPos->AddObject(bullet, x, y);
			ObjectMNG::GetMNG()->AddBullet(bullet);
			Small = true;
		}
		return this;
	}
	else { Small = false; }
	if (strncmp(Key_W, "1", 1) == 0) {
		if (Middle) { return this; }
		if (player->MBullet->Consumption(1))
		{
			Bullet* bullet = new Bullet(player->GetID(), MIDDLEBULLET, 5, 30.0f, new Shield(player->GetID(), x, y, SIZE / 2.3f), x, y, SIZE / 2.3f);
			player->StandPos->AddObject(bullet, x, y);
			ObjectMNG::GetMNG()->AddBullet(bullet);
			Middle = true;
		}
		return this;
	}
	else { Middle = false; }
	if (strncmp(Key_E, "1", 1) == 0) {
		if (Big) { return this; }
		if (player->BBullet->Consumption(1)) {
			Bullet* bullet = new Bullet(player->GetID(), BIGBULLET, 10, 90.f, new NonCharacteristic(), x, y, SIZE / 1.6f);
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