#include"State/BattleState/StateInBattle/Battle_State_Sub.h"
#include"Result.h"

Result::Result(Player* player,Player* enemy){
	if (*player->hp->GetVal() == 0.f && *enemy->hp->GetVal() == 0.f) {
		resultStr = "ひきわけ";
		portrate = player->portrate;
	}

	else if (*player->hp->GetVal() == 0.f) {
		resultStr = "まけ";
		portrate = enemy->portrate;
	}
	else if (*enemy->hp->GetVal() == 0.f) {
		resultStr = "かち";
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

/*試合を続けるか、IP入力画面に戻るかの選択*/
StateInBattle* Result::update(Battle_State* state){
	box->update();
	CutIn->Update();
	if (CutIn->Update()) {
		if (!wait) { Text = baseState->AddDrawObject((Field_Object*)select.get()); wait=true; }

		/*Player側の選択*/
		const char *KeyW = KeyBox::GetInstance()->
			updateframe->GetKey(PLAYER, WB);
		const char *KeyF = KeyBox::GetInstance()->
			updateframe->GetKey(PLAYER, FB);

		/*Fキーを押すと再度試合が始まる*/
		if (strncmp(KeyF, "1", 1) == 0) {
			box->SetMySelect(CONTINUE);
		}
		/*Wキーを押すとIP入力画面に戻る*/
		else if (strncmp(KeyW, "1", 1) == 0) {
			box->SetMySelect(ABORT);
		}


		/*Enmy側(通信相手)の選択*/
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

		/*どちらも選択したら選択結果を反映*/
		if(box->PlayerSelect != SELECTING && box ->EnemySelect != SELECTING){
			return new WaitingSelect(box);
		}


	}
	return this;
	}


/*
--------------------------SelectBox--------------------------
Player(ローカルプレイヤー),Enemy(通信相手)の試合後の選択を管理する
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

	string str = "F つづける  \n W おわる";
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

	/*どちらかが試合を終われば、片方が続ける選択をしても試合終了*/
	if (Select->PlayerSelect == ABORT || Select->EnemySelect == ABORT) {
		state->Abort();
	}
	else if (Select->PlayerSelect == CONTINUE && Select->EnemySelect == CONTINUE) {
		state->Reset();
	}

	return this;
}