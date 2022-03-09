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
	this->Panel = new CharacterPanel(x, y,portrate);
	start = new PanelMove(0, 30, Panel->Width);
	InMove = new PanelMove(1,40, Panel->Width);
	StayMove = new PanelMove(0,60, Panel->Width);
	start->Set(InMove);
	InMove->Set(StayMove);
	StayMove->Set(StayMove);
	State = start;

	wait = false;
	PanelNum = baseState->AddDrawObject((Field_Object*)this->Panel);

	box = new SelectBox();
	float ScreenWidth, ScreenHeight;
	SetScreenSize(&x, &y, &ScreenWidth, &ScreenHeight);
	select = new SelectNextState(x,y,ScreenWidth,ScreenHeight);
}

Result::~Result() {
	baseState->deleteObject(PanelNum);
	baseState->deleteObject(Text-1);
	delete start;
	delete Panel;
	delete InMove;
	delete StayMove;
	delete select;
}

/*試合を続けるか、IP入力画面に戻るかの選択*/
StateInBattle* Result::update(Battle_State* state){
	box->update();
	State = State->Update(Panel);
	if (State == StayMove && State->Finish()) {
		if (!wait) { Text = baseState->AddDrawObject((Field_Object*)select); wait=true; }

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
			delete this;
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
	Panel = new Primitive(SQUARE,x,y,0.f,
		ScreenWidth,ScreenHeight,
		0.5f,0.5f,0.5f,0.4f);

	Text = Font::GetInstance();
}

SelectNextState::~SelectNextState() {
	delete Panel;
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
	this->Select = box;
}

WaitingSelect::~WaitingSelect() {
	delete this->Select;
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