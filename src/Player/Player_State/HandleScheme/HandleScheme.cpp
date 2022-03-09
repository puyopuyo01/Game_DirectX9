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

	if (player->GetID() == ENEMY) { return this; } /*�f�o�b�O�p����*/

	if (strncmp(KeySpace, "1", 1) == 0){ 
		/*���̕K�E�Z�ɏ����K�E�Q�[�W��5*/
		if (player->Morale->Consumption(5)) {
			int power = 2;
			/*�D�����x���ɂ���Č��ʂ����܂�*/
			if (player->GetPredominant() > 0 && player->GetPredominant() <= LV1) { power = 3; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV2) { power = 4; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV3) { power = 5; }


			string name = "�H�십��";
			string intro = "�t�B�[���h�ɂ��鎩�g�̗H�����������B\n���̌��ʂ͗D�����x�����傫�����傫���B\n�������D�����x����������B";
			player->schemeBox->InsertScheme(new Enhancement(player->GetID(), power, 0.f,Panel_Field::GetPredAddr(),-2,player->portrate,name,intro));
		}

	}
	if (strncmp(KeyF, "1", 1) == 0){
		/*���̕K�E�Z�ɏ����K�E�Q�[�W��3*/
		if (player->Morale->Consumption(3)) {
			float speed = 10.f;
			/*�D�����x���ɂ���Č��ʂ����܂�*/
			if (player->GetPredominant() > 0 && player->GetPredominant() <= LV1) { speed = 15.f; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV2) { speed = 20.f; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV3) { speed = 25.f; }
			string name = "���x�㏸";
			string intro = "�t�B�[���h�ɂ��鎩�g�̗H��̑��x���㏸������B\n���̌��ʂ͗D�����x�����傫�����傫���B";
			player->schemeBox->InsertScheme(new Enhancement(player->GetID(),0,speed,Panel_Field::GetPredAddr(),0, player->portrate,name,intro));
		}

	}

	return this;

}


HandleScheme* SchemeWaitingForInput::Update(Player* player) {
	return this;
}