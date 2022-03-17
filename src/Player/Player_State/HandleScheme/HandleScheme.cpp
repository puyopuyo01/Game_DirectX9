#include"Player/Player_State/Player_State.h"
#include"Player/Scheme/Scheme.h"

HandleScheme* HandleScheme::Update(Player* player) { return nullptr; }

/*必殺技状態を管理するクラス(Bridgeパターンで実装)*/

HandleScheme* IdleScheme::Update(Player* player) {
	const char *KeySpace = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(), SPACE);
	const char *KeyF = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(),FB);
	const char *KeyG = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(), GB);

	if (player->GetID() == ENEMY) { return this; } /*デバッグ用処理*/

	if (strncmp(KeySpace, "1", 1) == 0){ 
		/*この必殺技に消費する必殺ゲージは5*/
		if (player->Morale->Consumption(5)) {
			int power = 2;
			/*優勢レベルによって効果が高まる*/
			if (player->GetPredominant() > 0 && player->GetPredominant() <= LV1) { power = 3; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV2) { power = 4; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV3) { power = 5; }


			string name = "幽霊強化";
			string intro = "フィールドにいる自身の幽霊を強化する。\nこの効果は優勢レベルが大きい程大きい。\nただし優勢レベルが下がる。";
			player->schemeBox->InsertScheme(new Enhancement(player->GetID(), power, 0.f,Panel_Field::GetPredAddr(),-2,player->portrate,name,intro));
		}

	}
	if (strncmp(KeyF, "1", 1) == 0){
		/*この必殺技に消費する必殺ゲージは3*/
		if (player->Morale->Consumption(3)) {
			float speed = 10.f;
			/*優勢レベルによって効果が高まる*/
			if (player->GetPredominant() > 0 && player->GetPredominant() <= LV1) { speed = 15.f; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV2) { speed = 20.f; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV3) { speed = 25.f; }
			string name = "速度上昇";
			string intro = "フィールドにいる自身の幽霊の速度を上昇させる。\nこの効果は優勢レベルが大きい程大きい。";
			player->schemeBox->InsertScheme(new Enhancement(player->GetID(),0,speed,Panel_Field::GetPredAddr(),0, player->portrate,name,intro));
		}

	}

	return this;

}


HandleScheme* SchemeWaitingForInput::Update(Player* player) {
	return this;
}