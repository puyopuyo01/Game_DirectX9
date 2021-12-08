#include"./Battle_State_Sub.h"
#include"State/CharacterPanel/CharacterPanel.h"


void InterputState::init(StateInBattle* next, int TextureNumber){
	name = "Interput";
	NextState = new WaitingNextState(10, next);
	float x, y;
	SetPosition(&x, &y);
	this->Panel = new CharacterPanel(x, y, TextureNumber);
	PanelNum = baseState->AddDrawObject((Field_Object*)this->Panel);
	InFrame = 30;
	OutFrame = 30;
	StayFrame = 90;
	InMove = new PanelMove(1, InFrame, Panel->Width);
	StayMove = new PanelMove(0, StayFrame, Panel->Width);
	OutMove = new PanelMove(-1, OutFrame, Panel->Width);
	InMove->Set(StayMove);
	StayMove->Set(OutMove);
	OutMove->Set(OutMove);
	State = InMove;

	TextNum = -1;

}


InterputState::InterputState(StateInBattle* next, int TextureNumber, string name, string intro) {
	init(next, TextureNumber);
	text = new TextBox(200,300,name,intro,30,90,30);
	TextNum = baseState->AddDrawObject((Field_Object*)this->text);
}
InterputState::~InterputState() {
	baseState->deleteObject(PanelNum);
	delete Panel; 
	delete InMove;
	delete StayMove;
	delete OutMove;
	if (text != nullptr) {
		baseState->deleteObject(TextNum - 1);
		delete text;
	}
}

StateInBattle* InterputState::update(Battle_State* state) {
	State = State->Update(Panel);
	text->Update();
	if (State == OutMove && State->Finish()) {
		delete this;
		return NextState;
	}

	return this;
}