#include"State/BattleState/StateInBattle/Battle_State_Sub.h"
#include"Result.h"

Result::Result(Player* player,Player* enemy){
	if (*player->hp->GetVal() == 0.f && *enemy->hp->GetVal() == 0.f) {
		resultStr = "�Ђ��킯";
		portrate = player->portrate;
	}

	else if (*player->hp->GetVal() == 0.f) {
		resultStr = "�܂�";
		portrate = enemy->portrate;
	}
	else if (*enemy->hp->GetVal() == 0.f) {
		resultStr = "����";
		portrate = player->portrate;
	}

	float x, y;
	SetPosition(&x, &y);
	CutIn = make_unique<CutInCharacter>(x, y, 60, 90, 30, portrate,1,0,0);


	wait = false;
	PanelNum = baseState->AddDrawObject((Field_Object*)CutIn->Panel.get());

	box = new SelectBox();
	float ScreenWidth, ScreenHeight;
	SetScreenSize(&x, &y, &ScreenWidth, &ScreenHeight);
	select = make_unique<SelectNextState>(x,y,ScreenWidth,ScreenHeight);
}

Result::~Result() {
	baseState->deleteObject(PanelNum);
	baseState->deleteObject(Text-1);
}

/*�����𑱂��邩�AIP���͉�ʂɖ߂邩�̑I��*/
StateInBattle* Result::update(Battle_State* state){
	box->update();
	CutIn->Update();
	if (CutIn->Update()) {
		if (!wait) { Text = baseState->AddDrawObject((Field_Object*)select.get()); wait=true; }

		/*Player���̑I��*/
		const char *KeyW = KeyBox::GetInstance()->
			updateframe->GetKey(PLAYER, WB);
		const char *KeyF = KeyBox::GetInstance()->
			updateframe->GetKey(PLAYER, FB);

		/*F�L�[�������ƍēx�������n�܂�*/
		if (strncmp(KeyF, "1", 1) == 0) {
			box->SetMySelect(CONTINUE);
		}
		/*W�L�[��������IP���͉�ʂɖ߂�*/
		else if (strncmp(KeyW, "1", 1) == 0) {
			box->SetMySelect(ABORT);
		}


		/*Enmy��(�ʐM����)�̑I��*/
		const char *KeyEnemW = KeyBox::GetInstance()->
			updateframe->GetKey(ENEMY, WB);
		const char *KeyEnemF = KeyBox::GetInstance()->
			updateframe->GetKey(ENEMY, FB);

		if (strncmp(KeyEnemF, "1", 1) == 0) {
			box->EnemySelect=CONTINUE;
		}
		else if (strncmp(KeyEnemW, "1", 1) == 0) {
			box->EnemySelect = ABORT;
		}

		/*�ǂ�����I��������I�����ʂ𔽉f*/
		if(box->PlayerSelect != SELECTING && box ->EnemySelect != SELECTING){
			return new WaitingSelect(box);
		}


	}
	return this;
	}


/*
--------------------------SelectBox--------------------------
Player(���[�J���v���C���[),Enemy(�ʐM����)�̎�����̑I�����Ǘ�����
*/

SelectBox::SelectBox() {
	PlayerSelect = SELECTING;
	EnemySelect = SELECTING;
}

void SelectBox::SetMySelect(int Select) {
	PlayerSelect = Select;
}

void SelectBox::update(){}

/*-------------------------SelectNextState---------------------*/
SelectNextState::SelectNextState(float x,float y,float ScreenWidth,float ScreenHeight):Field_Object(0.f,0.f,-1.f) {
	Panel = make_unique<Primitive>(SQUARE,x,y,0.f,
		ScreenWidth,ScreenHeight,
		0.5f,0.5f,0.5f,0.4f);

	Text = Font::GetInstance();
}

SelectNextState::~SelectNextState() {
}

void SelectNextState::Draw() {
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	Panel->Draw(this->GetMatrix());

	string str = "F �Â���  \n W �����";
	Text->Draw(0, 200, 1500, 1500, str.c_str());
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}


/*------------------------WaitingSelect------------------------*/
WaitingSelect::WaitingSelect(SelectBox* box) {
	this->Select = unique_ptr<SelectBox>(std::move(box));
}

WaitingSelect::~WaitingSelect() {
}

StateInBattle* WaitingSelect::update(Battle_State* state){

	/*�ǂ��炩���������I���΁A�Е���������I�������Ă������I��*/
	if (Select->PlayerSelect == ABORT || Select->EnemySelect == ABORT) {
		state->Abort();
	}
	else if (Select->PlayerSelect == CONTINUE && Select->EnemySelect == CONTINUE) {
		state->Reset();
	}

	return this;
}