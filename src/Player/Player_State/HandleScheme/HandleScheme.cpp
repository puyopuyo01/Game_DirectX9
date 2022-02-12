#include"Player/Player_State/Player_State.h"
#include"Player/Scheme/Scheme.h"

HandleScheme* HandleScheme::Update(Player* player) { return nullptr; }

/*�K�E�Z��Ԃ��Ǘ�����N���X(Bridge�p�^�[���Ŏ���)*/

HandleScheme* IdleScheme::Update(Player* player) {
	const char *KeySpace = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(), SPACE);
	const char *KeyF = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(),FB);
	const char *KeyG = KeyBox::GetInstance()->
		updateframe->GetKey(player->GetID(), GB);

	//if (player->GetID() == ENEMY) { return this; }

	if (strncmp(KeySpace, "1", 1) == 0){ 
		if (player->Morale->Consumption(5)) {
			string name = "�H�십��";
			string intro = "�t�B�[���h�ɂ��鎩�g�̗H�����������";
			player->schemeBox->InsertScheme(new Enhancement(player->GetID(), 5, 0.f, player->portrate,name,intro));
		}

	}
	if (strncmp(KeyF, "1", 1) == 0){
		if (player->Morale->Consumption(3)) {
			string name = "���x�㏸";
			string intro = "�t�B�[���h�ɂ��鎩�g�̗H��̑��x���㏸������";
			player->schemeBox->InsertScheme(new Enhancement(player->GetID(), 0, 15.f, player->portrate,name,intro));
		}

	}


	if (strncmp(KeyG, "1", 1) == 0){}

	return this;

}


HandleScheme* SchemeWaitingForInput::Update(Player* player) {
	return this;
}