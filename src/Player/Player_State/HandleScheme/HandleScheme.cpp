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

	if (strncmp(KeySpace, "1", 1) == MATCHKEYPRESS){
		/*���̕K�E�Z�ɏ����K�E�Q�[�W��5*/
		if (player->Morale->Consumption(5)) {
			int Power_Up = 2;
			/*�D�����x���ɂ���Č��ʂ����܂�*/
			if (player->GetPredominant() > 0 && player->GetPredominant() <= LV1) { Power_Up = 3; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV2) { Power_Up = 4; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV3) { Power_Up = 5; }


			string name = "�H�십��";
			string intro = "�t�B�[���h�ɂ��鎩�g�̗H�����������B\n���̌��ʂ͗D�����x�����傫�����傫���B\n�������D�����x����������B";
			player->schemeBox->InsertScheme(new Enhancement(player->GetID(), Power_Up, 0.f,Field_Move_Mass::GetPredAddr(),-2,player->portrate,name,intro));
		}

	}
	if (strncmp(KeyF, "1", 1) == MATCHKEYPRESS){
		/*���̕K�E�Z�ɏ����K�E�Q�[�W��3*/
		if (player->Morale->Consumption(3)) {
			float Speed_Up = 10.f;
			/*�D�����x���ɂ���Č��ʂ����܂�*/
			if (player->GetPredominant() > 0 && player->GetPredominant() <= LV1) { Speed_Up = 15.f; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV2) { Speed_Up = 20.f; }
			else if (player->GetPredominant() > 0 && player->GetPredominant() <= LV3) { Speed_Up = 25.f; }
			string name = "���x�㏸";
			string intro = "�t�B�[���h�ɂ��鎩�g�̗H��̑��x���㏸������B\n���̌��ʂ͗D�����x�����傫�����傫���B";
			player->schemeBox->InsertScheme(new Enhancement(player->GetID(),0,Speed_Up,Field_Move_Mass::GetPredAddr(),0, player->portrate,name,intro));
		}

	}

	return this;

}


HandleScheme* SchemeWaitingForInput::Update(Player* player) {
	return this;
}